import torch
import torch.nn as nn
from torch.autograd import Variable

# 交叉熵损失函数
celoss = nn.CrossEntropyLoss()


def train(net, trainset, criterion, optimizer, epoch_num=2):
    print("======== 开始进行训练 ========")

    loss_value = 0.0

    for epoch in range(1, epoch_num + 1):
        for idx, (images, labels) in enumerate(trainset):
            images = Variable(images)
            labels = Variable(labels)

            optimizer.zero_grad()  # 梯度归零

            outputs = net(images)  # 数据输进网络
            loss = criterion(outputs, labels)  # 计算损失值
            loss.backward()  # 进行反向传播
            optimizer.step()  # 优化器参数更新

            loss_value += loss.item()

            if idx % 2000 == 1999:
                loss_avg = loss_value / 2000  # 平均损失值
                loss_value = 0.0

                print(f"[{epoch}, {idx + 1:<5}] 平均损失值: {loss_avg:.5f}")

    print("========== 训练完成 ==========")


def test(net, testset, classes):
    correct = 0  # 预测正确数
    total = 0  # 总预测数

    for data in testset:
        images, labels = data
        outputs = net(Variable(images))
        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum()  # 预测正确的数目

    print(f"预测准确性: {100 * correct / total:.0f}%")

    # 每个分类的预测准确性
    correct = list(0.0 for _ in range(10))
    total = list(0.0 for _ in range(10))

    for data in testset:
        images, labels = data
        outputs = net(Variable(images))
        _, predicted = torch.max(outputs.data, 1)
        c = (predicted == labels).squeeze()

        for i in range(4):
            label = labels[i]
            correct[label] += c[i]
            total[label] += 1

    for i in range(10):
        p = 100 * correct[i] / total[i]
        print(f"分类 [{classes[i]:<5}] 的准确性为 {p:.0f}%")
