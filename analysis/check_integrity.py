#type: ignore
fp = open("analysis/mandelbrot-100-seq.hg")

g = (i.split(":") for i in fp.readlines())

ret = []
st = 0

for i, j in g:
    for l in i:
        if l == "[":
            st += 1
        elif l == "]":
            st -= 1
            if st < 0:
                break

    if st == 0:
        ret.append((i, j.removesuffix("\n")))
    st = 0

fp.close()

class Node:
    __slots__ = ("children", "idx", "terminal", "val")
    nodes = set()

    def __new__(cls, idx, val):
        self = super().__new__(cls)
        # print(1)
        self.terminal = False
        self.children = {}
        self.idx =  idx
        self.val = val
        return self

    def __bool__(self):
        return (not self.children)

    def add(self, idx, val):
        if (ch := self.children.get(val)) is not None:
            return ch

        if self.terminal:
            self.terminal = False
            Node.nodes.remove(self)

        self.children[val] = child = Node(idx, val)
        return child

    def __hash__(self):
        return hash((self.idx, self.val))

    def __str__(self):
        ret = ""
        for k, v in self.children.items():
            ret += f" {k}: ({v.__str__()})\n"
        return ret

ret2 = []
root = Node(None, "root")

def add_string(idx, string, node):
    for i in string:
        node = node.add(None, i)
        # print(node.val, id(node))
    node.idx = idx
    if node:
        node.terminal = True
        Node.nodes.add(node)

# for i, j in enumerate(ret):
#     add_string(i, j[0], root)
# #     print("----")

# # print(Node.nodes)

# for i in Node.nodes:
#     ret2.append(ret[i.idx])

fp = open("analysis/temp2.dat", "w+");
for i, j in ret:
    print(i, ":", j, sep="", file=fp);
fp.close();