#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<iterator>
#include<algorithm>
#include<cstdlib>
#include<map>


// CHANGE INFILE NAME BEFORE STARTING 
//std::string infile = "1";
std::string infile;
std::string outfile = "output/" + infile + "_out.txt";

std::map <int, std::vector<int>> adj_list_G;
std::vector<std::pair<int, int>> edges_G;
std::vector<std::pair<int, int>> edges_H;
std::vector<std::vector<int>> edge_list_H;
//std::vector<std::vector<int>> edges_G;

void adj_list_to_edges(std::map <int, std::vector<int>> graf) {
	/*std::vector<std::pair<int, int>> edges_G;*/
	std::vector<int> temp;

	for (auto it = graf.cbegin(); it != graf.cend(); ++it) {	
		for (auto& nastepnik : it->second) { 
			
			int poprzednik = it->first;		
			std::pair<int, int> krawedz = std::pair<int, int>(poprzednik, nastepnik);		
			edges_G.push_back(krawedz);
		}
	}		
	
}

void vec_of_vec_to_vec_of_pair(std::vector<std::vector<int>> vec_of_vec) {
	
	for (int i = 0; i < vec_of_vec.size(); i++) {		
		int v_p = vec_of_vec[i][0];
		int v_k = vec_of_vec[i][1];
		std::pair<int, int> krawedz = std::pair<int, int>(v_p, v_k);
		edges_H.push_back(krawedz);
	}
}


void save_dot_format(std::vector<std::pair<int, int>> edges, std::string graf_name) {
	std::string dotfile = "dot/" + graf_name + "_" + infile + ".dot";
	std::ofstream dot_file;
	dot_file.open(dotfile);
	if (dot_file.good() == true) {
		dot_file << "digraph {" << std::endl;
		/*dot_file << "landscape=true" << std::endl;*/
		int i = 1;
		//for (auto it = edges.begin(); it != edges.end(); it++) {
		//	/*dot_file << it->first << " -> " << it->second << "[label = " << '"'<< "a to b" <<'"]' << std::endl;*/
		//	if(graf_name == "H")
		//	dot_file << it->first << " -> " << it->second << " [label = " << '"' << i << '"' << ']' << std::endl;
		//	else {
		//		dot_file << it->first << " -> " << it->second << std::endl;
		//	}	
		//	i++;
		//}
		if (graf_name == "G") {
			for (auto it = adj_list_G.cbegin(); it != adj_list_G.cend(); ++it) {
				if (!it->second.empty()) {
					for (auto& nastepnik : it->second) {
						int poprzednik = it->first;
						dot_file << it->first << " -> " << nastepnik << std::endl;
					}
				}
				else {
					dot_file << it->first << std::endl;
				}		
			}
		}
		else if (graf_name == "H") {
			for (auto it = edges.cbegin(); it != edges.cend(); it++) {
				/*dot_file << it->first << " -> " << it->second << "[label = " << '"'<< "a to b" <<'"]' << std::endl;*/
				dot_file << it->first << " -> " << it->second << " [label = " << '"' << i << '"' << ']' << std::endl;
				i++;
			}
		}
		dot_file << "}";
		std::cout << std::endl;
		std::cout << "zapisano plik DOT:"<< dotfile << std::endl;
	}
	else {
		std::cout << "Błąd! Nie można zapisać pliku" << std::endl;
	}
	dot_file.close();
}


void read_graph_from_file(std::string infile) {
	std::string infile_path = "input/" + infile + ".txt";
	std::ifstream read_file(infile_path.c_str());
	if (read_file.fail()) {
		std::cerr << "Nie można otworzyc pliku! " << infile << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Wczytywanie pliku: " << infile << std::endl;
	std::cout << std::endl;
	std::string line;
	while (std::getline(read_file, line)) {
		std::istringstream ss_line(line);
		std::vector<int> curr_vertex_succesors;
		std::vector<int> vertexes;
		int v;
		int curr_vertex = 0;
		int char_position = 0;
		while (ss_line >> v) {
			if (char_position == 0) {
				curr_vertex = v;
			}
			else {
				curr_vertex_succesors.push_back(v);
			}
			char_position++;
		}		
		//std::sort(curr_vertex_succesors.begin(), curr_vertex_succesors.end());
		adj_list_G.insert(std::pair<int, std::vector<int>>(curr_vertex, curr_vertex_succesors));

	}
	read_file.close();
}


void print_curr_vertex_successors(std::map <int, std::vector<int>> graf, int vertex_id) {
	std::cout << std::endl;
	auto it = graf.find(vertex_id);
	std::cout << it->first << ": ";
	for (auto nastepnik = it->second.cbegin(); nastepnik != it->second.cend(); ++nastepnik) {
		std::cout << *nastepnik << " ";
	}
}


void print_graph(std::map <int, std::vector<int>> graf) {
	for (auto it = graf.cbegin(); it != graf.cend(); ++it)
	{
		std::cout << it->first << ": ";
		for (auto nastepnik = it->second.cbegin(); nastepnik != it->second.cend(); ++nastepnik) {
			std::cout << *nastepnik << " ";
		}
		std::cout << std::endl;
	}
}


void save_to_file(int h_iter, std::string outfile, std::map <int, std::vector<int>> graf) {
	std::cout << std::endl;
	std::cout << "--------------- " << std::endl;
	std::cout << "Graf H: " << std::endl;
	std::ofstream out_file;
	out_file.open(outfile);
	if (out_file.good() == true) {
		//wypisuje W 
		for (int i = 1; i < h_iter; i++) {
			out_file << i << " ";
			std::cout << i << ": ";
			//wypisuje nast W
			for (int j = 0; j < graf.size(); j++) {
				if (edge_list_H[j][0] == i) {
					out_file << edge_list_H[j][1] << " ";
					std::cout << edge_list_H[j][1] << " ";
				}
			}
			out_file << "\n";
			std::cout << std::endl;
		}
		std::cout << "--------------- " << std::endl;
		std::cout << std::endl;
		std::cout << "Zapisano do pliku: " << outfile << std::endl;
	}
	else {
		std::cout << "Błąd! Nie można zapisać pliku" << std::endl;
	}

}


void print_vector_of_vector(std::vector<std::vector<int>> vec_of_vec) {
	for (const auto& row : vec_of_vec) {
		for (const auto& node : row) {
			std::cout << node << ' ';
		}
		std::cout << std::endl;
	}
}


void print_transf(std::map <int, std::vector<int>> graf) {
	std::cout << "V(G)	E(H)" << std::endl;
	for (int i = 0; i < graf.size(); i++) {
		std::cout << i + 1 << "	";
		for (int j = 0; j < edge_list_H[i].size(); j++) {
			std::cout << edge_list_H[i][j] << "  ";
		}
		std::cout << std::endl;
	}

}


void transform(std::map <int, std::vector<int>> graf) {
	std::cout << std::endl;
	std::cout << "***TRANSFORMACJA*** " << std::endl;
	std::cout << std::endl;
	int v_p = 1;
	int nast_w_G, wp, wk;
	for (auto vert = graf.cbegin(); vert != graf.cend(); ++vert) {
		int v_k = vert->first * 2;		
		std::vector<int>list;
		list.push_back(v_p);
		list.push_back(v_k);
		edge_list_H.push_back(list);
		v_p += 2;
	}
	/*std::cout << std::endl;
	std::cout << "############" << std::endl;
	print_transf(graf);
	std::cout << "############" << std::endl;*/
	for (auto vert = graf.cbegin(); vert != graf.cend(); ++vert) {
		int w_G = vert->first;
		for (auto succ = vert->second.cbegin(); succ != vert->second.cend(); ++succ) {
			nast_w_G = *succ;			
			wp = edge_list_H[nast_w_G - 1][0];	  	
			wk = edge_list_H[w_G - 1][1];	     
			edge_list_H[nast_w_G - 1][0] = wk; 
			for (int it = 0; it < graf.size(); it++) {
				if (edge_list_H[it][0] == wp) {
					edge_list_H[it][0] = wk;
				}
				if (edge_list_H[it][1] == wp) {
					edge_list_H[it][1] = wk;
				}
			}
		}
	}
	/*std::cout << std::endl;
	std::cout << "*****************" << std::endl;
	print_transf(graf);
	std::cout << "*****************" << std::endl;*/

	//indeksowanie aby zachowac numeracje rosnaco od 1
	int h_iter = 1;
	for (int it = 0; it < graf.size(); it++) {
		for (int n = 0; n < edge_list_H[it].size(); n++) {
			//jesli skladowa luku- n >=hiter to porownujemy ją z pozostalymi skl innych lukow 
			if (edge_list_H[it][n] >= h_iter) {
				int graf_H_it_n = edge_list_H[it][n];
				for (int it2 = 0; it2 < graf.size(); it2++) {
					for (int m = 0; m <= 1; m++) {
						// jesli jakis W w luku == innemu W to zamieniamy jego wartosc na iter
						if (edge_list_H[it2][m] == graf_H_it_n) {
							edge_list_H[it2][m] = h_iter;
						}
					}
				}
				h_iter++;
			}
		}
	}
	print_transf(graf);
	vec_of_vec_to_vec_of_pair(edge_list_H);
	save_dot_format(edges_H, "H");
	save_to_file(h_iter, outfile, graf);
}


bool linearity(std::map <int, std::vector<int>> graf) {
	/*1-graf G jest skierowanym grafem liniowym, wtedy i tylko wtedy, 
	gdy dla wszystkich jego par wierzchołków x i y spełniony jest warunek:

	N+(x) ∩ N+(y) ≠ Ø ⇒ ( N+(x) = N+(y) ∧ N–(x) ∩ N–(y) = Ø ),
	gdzie N–(x) oznacza zbiór bezpośrednich poprzedników x.
	*/
	int succ1_val, succ2_val;
	int vert_start_val = 1;
	for (auto vert_start = graf.cbegin(); vert_start != graf.cend(); ++vert_start) {		
		if (vert_start->second.size() > 1) {			
			for (auto succ1 = vert_start->second.cbegin(); succ1 != vert_start->second.cend(); ++succ1) {
				for (auto succ2 = vert_start->second.cbegin(); succ2 != vert_start->second.cend(); ++succ2) {					
					succ1_val = *succ1;
					succ2_val = *succ2;
					if (succ1_val != succ2_val) {						
						for (auto succ_of_succ1 = graf.find(succ1_val)->second.cbegin(); succ_of_succ1 < graf.find(succ1_val)->second.cend(); ++succ_of_succ1) {
							for (auto succ_of_succ2 = graf.find(succ2_val)->second.cbegin(); succ_of_succ2 < graf.find(succ2_val)->second.cend(); ++succ_of_succ2) {								
								int succ_of_succ1_val = *succ_of_succ1;
								int succ_of_succ2_val = *succ_of_succ2;
								if (*succ_of_succ1 == *succ_of_succ2) {
									std::cout << "nie liniowy |" << std::endl;	
									return false;
								}								
							}							
						}
					}
					
				}
			}
		}
		vert_start_val++;
	}
	std::cout << "liniowy |" << std::endl;
	return true;
}


int adjoint(std::map <int, std::vector<int>> graf) {

	bool same = false;
	std::cout << std::endl;
	for (auto vert1 = graf.cbegin(); vert1 != std::prev(graf.cend()); ++vert1) {
		if (vert1->second.size() > 1) {
			const auto duplicate = std::adjacent_find(vert1->second.cbegin(), vert1->second.cend());
			if (duplicate != vert1->second.end()){
				std::cout << "Multigraf, wielokrotna krawedz:  " << vert1->first << " -> " << *duplicate << "\n";
				return 0;
			}				
			/*for (auto succ1 = vert1->second.cbegin(); succ1 != vert1->second.cend(); ++succ1) {
				for (auto succ2 = std::next(succ1); succ2 != vert1->second.cend(); ++succ2) {
					if (*succ1 == *succ2) {
						std::cout << vert1->first;
						std::cout << ": " << "a " << *succ1 << "  b " << *succ2 << std::endl;
						std::cout << "! multi graf !" << std::endl;
						std::cout << "| !GRAF NIESPRZEZONY! |" << std::endl;
						return 0;
					}
				}
			}*/
		}
		for (auto vert2 = std::next(graf.cbegin()); vert2 != graf.cend(); ++vert2) {			
			if (vert1 != vert2) {
				//std::cout << std::endl;
				//std::cout << "A:" << vert1->first;
				//std::cout << " B:" << vert2->first;				
				if (vert1->second == vert2->second) {
					same = true;					
				}				
				else if (vert1->second.size() >= 1 && vert2->second.size() >= 1) {
					for (auto succ1 = vert1->second.cbegin(); succ1 != vert1->second.cend(); ++succ1) {
						for (auto succ2 = vert2->second.cbegin(); succ2 != vert2->second.cend(); ++succ2) {
							if (*succ1 == *succ2) {
								std::cout << " " << *succ1 << " == " << *succ2 << " not ok ";
								std::cout << "| !GRAF NIESPRZEZONY! |" << std::endl;
								same = false;
								return 0;
							}
							else {
								same = true;								
								//std::cout <<  std::endl;								
								//std::cout << " " << *succ1 << " != " << *succ2;
								//std::cout << "  ok " << std::endl;
							}
						}
					}
					if (same == false) {
						std::cout << " not same ";
						std::cout << "| !GRAF NIESPRZEZONY! |" << std::endl;
						return 0;
					}
				}
			}
		}
	}
	if (same == true) {
		std::cout << "| graf sprzezony |";
		return 1;
	}
}


int main()
{
	std::cout << "Podaj nazwe pliku: " << std::endl;
	std::cin >> infile;
	read_graph_from_file(infile);
	std::cout << "Graf wejsciowy G: " << std::endl;
	print_graph(adj_list_G);
	adj_list_to_edges(adj_list_G);
	save_dot_format(edges_G, "G");
	//print_vector_of_vector(edges_G);
	//print_curr_vertex_successors(graf_G,8);
	//print_vector_of_vector(adj_list);
	if (adjoint(adj_list_G)) {		 
			linearity(adj_list_G);
			transform(adj_list_G);	
	};	
	return 0;
}
