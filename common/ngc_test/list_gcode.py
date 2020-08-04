with open('micro5_3axes_ebauche.ngc', 'r') as f:
    words = f.read().split()

words = filter(None, words)
words = filter(lambda w: w[0] == 'G' or w[0] == 'M', words)
print(set(words))