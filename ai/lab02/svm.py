import torch.nn as nn


class SVM(nn.Module):
    def __init__(self):
        super().__init__()
        self.fc = nn.Linear(32 * 32 * 3, 10, bias=True)

    def forward(self, x):
        x = x.view(x.size(0), -1)
        x = self.fc(x)
        return x
