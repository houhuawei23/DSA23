n = int(input())  # 任务数量
times = list(map(int, input().split()))  # 任务准备时间列表
values = list(map(int, input().split()))  # 任务性价比列表

tasks = list(zip(times, values))  # 将准备时间和性价比组合成任务列表
tasks.sort(key=lambda x: -x[1])  # 按性价比从高到低排序

current_time = 0  # 当前时间点
total_value = 0  # 总收益

for task in tasks:
    start_time = task[0]  # 任务的开始时间
    end_time = task[0] + task[0]  # 任务的结束时间

    if start_time > current_time:  # 判断任务的开始时间是否晚于当前时间点
        current_time = start_time  # 更新当前时间点

    if end_time <= current_time:  # 判断任务的结束时间是否早于等于当前时间点
        total_value += task[1]  # 累加任务的性价比到总收益
        current_time += 1  # 更新当前时间点

print(total_value)
