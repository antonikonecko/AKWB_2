import networkx as nx
import matplotlib
import sys

matplotlib.use('Agg')
import matplotlib.pyplot as plt


def read_graph(filename):
    graph_adjacency_list = { }
    for line in open(filename):
        line = map(int, line.rstrip("\t\r\n").split("\t"))
        graph_adjacency_list.update({ line[0]: { e: 1 for e in line[1:] } })

    return graph_adjacency_list


fil = str(sys.argv[1])
graph_data = read_graph(fil)
G = nx.Graph(graph_data)
nx.draw_networkx(G, with_labels = True, node_color = "c", edge_color = "k", font_size = 8)

out_filename = fil + ".pdf"
plt.axis('off')
plt.draw()
plt.savefig("out_filename")
