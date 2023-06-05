from sklearn.manifold import LocallyLinearEmbedding
import numpy as np
import torch

# 读入原始数据并将其转换为2D矩阵（145*145*200行，200列）
# data = np.load('数据路径')
data = np.random.rand(20, 20, 50)
data = torch.from_numpy(data)
X = data.reshape(-1, 50)

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
print(device)
X = X.to(device)

# 使用LocallyLinearEmbedding对数据进行降维
lle = LocallyLinearEmbedding(n_components=20, n_neighbors=10)
X_lle = lle.fit_transform(X)

X_lle = X_lle.cpu().numpy()
# 将降维后的数据重构回原本的3D矩阵形式（145*145*20）
X_3d = X_lle.reshape(20, 20, 20)

# 输出结果
print(X_3d.shape)