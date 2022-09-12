# type: ignore

from collections import Counter

# accumulator = Counter()
ctr = Counter()

fn = "mandelbrot"
with open(f"examples/{fn}.bf", "r") as fp:
    text = fp.read()

max_seq = 100
# insts = {
#     ">", "<", "+", "-", ".", ",", "[", "]"
# }

# map_i = {
#     c: idx for idx, c in enumerate(insts)
# }

imap = {
    ">": 0b0000,
    "<": 0b0001,
    "+": 0b0010,
    "-": 0b0011,
    ".": 0b0100,
    ",": 0b0101,
    "[": 0b0110,
    "]": 0b0111,
}

l = [None] * len(imap)

for k ,v in imap.items():
    l[v] = k

arr = bytes(j for j in (imap.get(i) for i in text) if j is not None)

text = memoryview(arr).toreadonly()

hi = 150
lo = 2

for i in range(len(text) - hi):
    for j in range(lo + 1, hi + 1):
        ctr[text[i:i+j]] += 1

fp = open(f"analysis/{fn}-{max_seq}-seq.hg", "w")

print("\n".join(
        str(k) + ":" + str(v) for k, v in sorted(
            map(lambda it: (
                "".join(map(lambda n: l[n], it[0])), it[1]
                ),
                ctr.items()
            ),
            key=lambda it: it[1],
            reverse=True
        )
    ),
    file=fp,
)
fp.close()

# text = list(map(lambda c: map_i[c], filter(lambda c: c in insts, text)))

# from prefixspan import PrefixSpan
# ps = PrefixSpan([text,])

# ps.maxlen = 150
# ps.minlen = 2

# [print("".join(l[i] for i in patt), ":", freq) for freq, patt in ps.topk(10, filter=lambda patt, matches: len(set(patt)) > 1)]

# s = []
# for idx, i in enumerate(text):
#     if i == "[":
#         s.append(idx)
#     elif i == "]":
#         accumulator[text[s.pop():idx+1]] += 1

