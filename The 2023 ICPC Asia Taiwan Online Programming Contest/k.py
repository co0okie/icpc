s = input()
print(sum([1 if s[i:i+4] == 'kick' else 0 for i in range(len(s))]))