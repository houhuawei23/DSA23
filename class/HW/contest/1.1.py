n = int(input())  # 任务数量
t = list(map(int, input().split()))  # 任务准备时间列表
p = list(map(int, input().split()))  # 任务性价比列表

def maximize_profit(n, times, profits):
    # 对工作按结束时间进行排序
    # jobs = sorted(zip(times, profits))
    jobs = list(zip(times, profits))
    print(jobs)
    # 初始化 dp 数组
    dp = [0] * (n+1)
    
    for i in range(1, n+1):

        
        # 计算 dp[i]
        dp[i] = max(dp[i-1], dp[j] + jobs[i-1][1])
    
    return dp[n]

print(maximize_profit(n, t, p))