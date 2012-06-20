# python EachTweetCounts.py
chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890()[]{}<>!@#$%^&*~`-_=+|;:,./?"\\\' '
tweet = [0]

def right(a):
  if a < len(tweet):
    tweet[a] = (tweet[a]+1) % len(chars)
    if tweet[a] == 0:
      right(a+1)
  elif a < 140 and a == len(tweet):
    tweet.append(0)

while len(tweet) < 141:
  status = ""
  for i in range(len(tweet)):
    status += chars[tweet[i]]

  print status

  tweet[0] = (tweet[0]+1) % len(chars)

  if tweet[0] == 0:
    right(1)