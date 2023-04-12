import torch.optim as optim
from dataset import CIFAR10
from tool import train, test, celoss
import torch.nn.functional as F
from cnn import CNN
from fcnn import FCNN
from rnn import RNN
from svm import SVM


def run_cnn(ds: CIFAR10):
    print("======== 卷积神经网络 ========")

    net = CNN()

    # 随机梯度下降
    sgd = optim.SGD(
        net.parameters(),
        lr=0.001,
        momentum=0.9,
    )

    train(net, ds.TRAINSET, celoss, sgd)
    test(net, ds.TESTSET, ds.CLASSES)


def run_rnn(ds: CIFAR10):
    print("======== 循环神经网络 ========")

    net = RNN()

    adam = optim.Adam(
        net.parameters(),
        lr=0.01,
    )

    train(net, ds.TRAINSET, celoss, adam)
    test(net, ds.TESTSET, ds.CLASSES)


def run_fcnn(ds: CIFAR10):
    print("======= 全连接神经网络 =======")

    net = FCNN()

    sgd = optim.SGD(
        net.parameters(),
        lr=0.001,
        momentum=0.9,
    )

    train(net, ds.TRAINSET, celoss, sgd)
    test(net, ds.TESTSET, ds.CLASSES)


def run_svm(ds: CIFAR10):
    print("========= 支持向量机 =========")

    svm = SVM()

    sgd = optim.SGD(
        svm.parameters(),
        lr=0.001,
        momentum=0,
    )

    train(svm, ds.TRAINSET, F.multi_margin_loss, sgd)
    test(svm, ds.TESTSET, ds.CLASSES)


def main():
    ds = CIFAR10()

    # run_cnn(ds)
    # run_fcnn(ds)
    # run_rnn(ds)
    run_svm(ds)


if __name__ == "__main__":
    main()
