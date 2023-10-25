import numpy as np

k, n, m = int(input()), int(input()), int(input())
colors = [int(i) for i in input().strip().split()]
initial_probabilities = [float(i) for i in input().strip().split()]
transitions = [[] for _ in range(n)]
for i in range(n):
    transitions[i] = [float(i) for i in input().strip().split()]
colors_probabilities = [[] for _ in range(n)]
for i in range(n):
    colors_probabilities[i] = [float(i) for i in input().strip().split()]

next_probabilities = np.array(initial_probabilities.copy())
for _ in range(k):
    next_probabilities = np.matmul(next_probabilities, transitions)
final_colors = np.matmul(next_probabilities, np.array(colors_probabilities))

max_value = max(final_colors)
final_color = 0
for i in range(len(final_colors)):
    if final_colors[i] == max_value:
        final_color = i + 1
print(final_color, round(final_colors[final_color - 1], 2))
