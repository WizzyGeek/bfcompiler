# type: ignore

from collections import Counter

accumulator = Counter()

fn = "mandelbrot"
with open(f"examples/{fn}.bf", "r") as fp:
    text = fp.read()

max_seq = 100
insts = {
    ">", "<", "+", "-", ".", ",", "[", "]"
}

text = "".join(filter(lambda c: c in insts, text))

s = []
for idx, i in enumerate(text):
    if i == "[":
        s.append(idx)
    elif i == "]":
        accumulator[text[s.pop():idx+1]] += 1

fp = open(f"analysis/{fn}-{max_seq}-seq.hg", "w")
print("\n".join(str(k) + ":" + str(v) for k, v in sorted(((t, c) for t, c in accumulator.items()), key=lambda a: a[1], reverse=True) if len(k) <= max_seq), file=fp)
fp.close()