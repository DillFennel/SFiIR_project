#!/usr/bin/env python3
import matplotlib.pyplot as plt

fig, axes = plt.subplots(4, 3, figsize=(6, 8))  # 2 строки, 3 столбец
axes[0][2].remove()
axes[3][2].remove()
with open('test_distribution_data.txt', 'r') as file:
	content = file.readlines()
n, k = map(int, content[0].split(" "))
t_p_y = []
t_p_x = []
t_obr_y = []
t_obr_x = []

t_p_x_glob = [1, 2, 3, 4, 5, 6]
t_p_y_glob = [0, 0, 0, 0, 0, 0]
t_obr_x_glob = [1, 2, 3, 4, 5, 6]
t_obr_y_glob = [0, 0, 0, 0, 0, 0]

start = 3
for k1 in range(0, k):
	t_p_y.append([])
	t_p_x.append([])
	for i in range(0, 6):
		str = content[start].split(" ")
		t_p_y[k1].append(int(str[1]))
		t_p_x[k1].append(int(str[0][:-1]))
		t_p_y_glob[i] += int(str[1])
		start += 1
	start += 1
start += 1
for k1 in range(0, k):
	t_obr_x.append([])
	t_obr_y.append([])
	for i in range(0, 6):
		str = content[start].split(" ")
		t_obr_y[k1].append(int(str[1]))
		t_obr_x[k1].append(int(str[0][:-1]))
		t_obr_y_glob[i] += int(str[1])
		start += 1
	start += 1
axes[0][0].set_title(f'Графики частоты появления чисел на выборке из {n} запусков')
axes[0][0].set_xlabel('Ось х (значение t)')
axes[0][0].set_ylabel('Ось y (частота появления)')
axes[0][0].set_xlim([1, 6])
axes[0][0].set_ylim([0, 3000])
axes[0][1].set_xlim([1, 6])
axes[0][1].set_ylim([0, 3000])
axes[0][0].plot(t_p_x_glob, t_p_y_glob, color = 'g', label = 't_p')
axes[0][1].plot(t_obr_x_glob, t_obr_y_glob, color = 'r', label = 't_obr')
axes[1][0].set_title('Графики частоты появления чисел в каждой трети')
for y in range(1, 3):
	for x in range(0, 3):
		axes[y][x].set_xlim([1, 6])
		axes[y][x].set_ylim([0, 1000])
		if y == 1:
			axes[y][x].plot(t_p_x[x], t_p_y[x], color = 'g', label = 't_p')
		else:
			axes[y][x].plot(t_obr_x[x], t_obr_y[x], color = 'r', label = 't_obr')
axes[3][0].set_title('Целевые графики t_p и t_obr, к которым нужно стремиться')
axes[3][0].plot([1, 2, 3, 4, 5, 6],[25, 23, 21, 12, 9, 10], color = 'g') 
axes[3][1].plot([1, 2, 3, 4, 5, 6],[6, 15, 27, 29, 6, 17], color = 'r')
plt.show()
