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
std::string infile = "sample_graph";
std::string outfile = "out_" + infile;
std::map <int, std::vector<int>> graf_G;
std::vector<std::vector<int>> graf_H;

void read_graph_from_file(std::string infile) {
	std::ifstream read_file(infile.c_str());
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
		//  gdyby nastepniki byly w roznej kolejnosci
		std::sort(curr_vertex_succesors.begin(), curr_vertex_succesors.end());
		graf_G.insert(std::pair<int, std::vector<int>>(curr_vertex, curr_vertex_succesors));

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
	for (auto it = graf.begin(); it != graf.end(); ++it)
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
				if (graf_H[j][0] == i) {
					out_file << graf_H[j][1] << " ";
					std::cout << graf_H[j][1] << " ";
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

int jeden_graf(std::map <int, std::vector<int>> graf) {
	for (auto vert = graf.cbegin(); vert != graf.cend(); ++vert) {
		if (vert->second.size() > 1) {
			for (auto succ1 = vert->second.cbegin(); succ1 != vert->second.cend(); ++succ1) {
				for (auto succ2 = std::next(succ1); succ2 != vert->second.cend(); ++succ2) {
					if (*succ1 == *succ2) {
						std::cout << vert->first;
						std::cout << ": " << "a " << *succ1 << "  b " << *succ2 << std::endl;
						std::cout << "! multi graf !" << std::endl;
						return 0;
					}
				}
			}
		}
		//std::cout<< vert->first << "OK" << std::endl;

	}
	std::cout << " 1-graf | ";
	return 1;
}


void print_transf(std::map <int, std::vector<int>> graf) {
	std::cout << "V(G)	E(H)" << std::endl;
	for (int i = 0; i < graf.size(); i++) {
		std::cout << i + 1 << "	";
		for (int j = 0; j < graf_H[i].size(); j++) {
			std::cout << graf_H[i][j] << "  ";
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
	//	dla kazdego W w G tworzymy luk w H
	// inicjujemy wektor krawedzi gdzie a= nr W z G, b i c to W tworzące luk w H
	for (auto vert = graf.cbegin(); vert != graf.cend(); ++vert) {

		int v_k = vert->first * 2;
		/*std::cout << "v-g: " << v_g << std::endl;
		std::cout << "  v-p: " << v_p;
		std::cout << "  v-k: " << v_k << std::endl;*/
		std::vector<int>list;

		list.push_back(v_p);
		list.push_back(v_k);
		graf_H.push_back(list);
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
			wk = graf_H[w_G - 1][1];		     // kolumna 3 c w wektorze krawedzi x == W koncowy luku w H z Wx w G (-1 bo w c++ tablica od zera)
			wp = graf_H[nast_w_G - 1][0];	// == W. początkowy luku H z ktorego powstal W [nast_wx_G - 1]			
			graf_H[nast_w_G - 1][0] = wk;  // zmieniamy wart kolumny1 b na wart kol2 c 
			for (int it = 0; it < graf.size(); it++) {
				if (graf_H[it][0] == wp) {
					graf_H[it][0] = wk;
				}
				if (graf_H[it][1] == wp) {
					graf_H[it][1] = wk;
				}
			}
		}
	}
	/*std::cout << std::endl;
	std::cout << "*****************" << std::endl;
	print_transf(graf);
	std::cout << "*****************" << std::endl;*/

	//kompresja 
	int h_iter = 1;
	for (int it = 0; it < graf.size(); it++) {
		for (int n = 0; n < graf_H[it].size(); n++) {
			//jesli skladowa luku- n >=que to porownujemy ją z pozostalymi skl innych lukow 
			if (graf_H[it][n] >= h_iter) {
				int graf_H_it_n = graf_H[it][n];
				for (int it2 = 0; it2 < graf.size(); it2++) {
					for (int m = 0; m <= 1; m++) {
						// jesli jakis W w luku == innemu W to zamieniamy jego wartosc na que
						if (graf_H[it2][m] == graf_H_it_n) {
							graf_H[it2][m] = h_iter;
						}
					}
				}
				h_iter++;
			}
		}
	}
	//wyswietl z ktorych lukow powstaly wierzcholki	
	print_transf(graf);
	save_to_file(h_iter, outfile, graf);
}


bool liniowosc(std::map <int, std::vector<int>> graf) {
	int zbior1, zbior2;
	for (auto vert = graf.cbegin(); vert != graf.cend(); ++vert) {
		// tam gdzie wiecej niz 2 elementy zapamietujemy jako z1 i z2
		if (vert->second.size() > 1) {
			//d i k iteruja po linii 
			for (auto succ1 = vert->second.cbegin(); succ1 != vert->second.cend(); ++succ1) {
				for (auto succ2 = std::next(succ1); succ2 != vert->second.cend(); ++succ2) {
					zbior1 = *succ1;
					zbior2 = *succ2;

					for (auto xy = graf.find(zbior1)->second.cbegin(); xy < graf.find(zbior1)->second.cend(); ++xy) {
						for (auto zz = graf.find(zbior1)->second.cbegin(); zz < graf.find(zbior1)->second.cend(); ++zz) {
							//jeśli poprzedniki takie same
							if (*xy == *zz) {
								std::cout << "nie liniowy |" << std::endl;
								return false;
							}
						}
					}
				}
			}
		}
	}
	std::cout << "liniowy |" << std::endl;
	return true;
}


int check(std::map <int, std::vector<int>> graf) {

	bool same = false;
	std::cout << std::endl;

	for (auto vert1 = graf.cbegin(); vert1 != std::prev(graf.cend()); ++vert1) {
		for (auto vert2 = std::next(graf.cbegin()); vert2 != graf.cend(); ++vert2) {
			//nie porownuje tych samych
			if (vert1 != vert2) {
				//std::cout << std::endl;
				//std::cout << "A:" << vert1->first;
				//std::cout << " B:" << vert2->first;
				//jesli cały zbior nastepników jest taki sam:
				if (vert1->second == vert2->second) {
					same = true;
					//std::cout << " same ";
				}
				//jesli nie jest taki sam to:
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
	read_graph_from_file(infile);
	std::cout << "Graf wejsciowy G: " << std::endl;
	print_graph(graf_G);

	//print_curr_vertex_successors(graf_G,8);
	//print_vector_of_vector(adj_list);
	if (check(graf_G)) {
		if (jeden_graf(graf_G)) {
			liniowosc(graf_G);
			transform(graf_G);
		};

	};
	return 0;
}
