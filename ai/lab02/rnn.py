import torch.nn as nn


class RNN(nn.Module):
    def __init__(self):
        super().__init__()

        self.lstm = nn.LSTM(32 * 3, 128, batch_first=True, num_layers=5)
        self.line1 = nn.Linear(128, 128)
        self.line2 = nn.Linear(128, 10)

    # 前向传播
    def forward(self, x):
        x = x.view(-1, 32, 32 * 3)
        x, _ = self.lstm(x)
        x = self.line1(x[:, -1, :])
        x = self.line2(x)

        return x
