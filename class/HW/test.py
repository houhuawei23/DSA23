import numpy as np
import matplotlib.pyplot as plt

# Constants
N = 100  # Number of spatial points
M = 1000  # Number of time points
L = 1  # Length of the domain
T = 1  # Total time
dx = L / N  # Spatial step size
dt = T / M  # Time step size

# Initialize arrays
C = np.zeros((N+1, M+1))  # Concentration
J = np.zeros((N+1, M+1))  # Flux

# Initial condition function
def phi(x):
    phi = np.zeros_like(x)
    phi[x < 0.6] = 0
    phi[(x >= 0.6) & (x <= 1)] = 0.08
    phi[x > 1] = 0
    return phi

# Initialize C with initial condition
x = np.linspace(0, L, N+1)
C[:, 0] = phi(x)

# Boundary conditions
J[0, :] = 0
J[N, :] = 0

# Numerical solution
for j in range(M): # Time loop
    for i in range(1, N): # Space loop
        J[i, j] = -(C[i+1, j] - C[i-1, j]) / (2*dx)

    for i in range(1, N):
        C[i, j+1] = C[i, j] - (dt/(2*dx)) * (J[i+1, j] - J[i-1, j])

# Plotting
X, T = np.meshgrid(x, np.linspace(0, T, M+1))
fig = plt.figure()
ax = fig.gca(projection='3d')
ax.plot_surface(T, X, C, cmap='viridis')
ax.set_xlabel('Time (t)')
ax.set_ylabel('Position (x)')
ax.set_zlabel('Concentration (C)')
ax.set_title('Numerical Solution')
plt.show()
