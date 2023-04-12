from torch.utils.data import DataLoader
import torchvision.datasets as dset
import torchvision.transforms as transforms

_transform = transforms.Compose(
    [
        transforms.ToTensor(),
        transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5)),
    ],
)


def _load_CIFAR(src, train):
    return DataLoader(
        dset.CIFAR10(
            src,
            train=train,  # 是否是训练集
            transform=_transform,
            download=True,
        ),
        batch_size=4,  # 每次加载多少个样本
        shuffle=True,  # 打乱数据
        num_workers=2,
    )


class CIFAR10:
    CLASSES = (
        "plane",
        "car",
        "bird",
        "cat",
        "deer",
        "dog",
        "frog",
        "horse",
        "ship",
        "truck",
    )  # 类别

    def __init__(self, src="./data"):
        self.TRAINSET = _load_CIFAR(src, True)  # 训练集
        self.TESTSET = _load_CIFAR(src, False)  # 测试集
