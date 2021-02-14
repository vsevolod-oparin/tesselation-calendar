#include <vector>
#include <map>
#include <iostream>
#include <fstream> 
#include <sstream>

typedef uint64_t field_t;
typedef uint16_t pent_set_t;

struct pentamino {
	uint16_t p_id;
	uint64_t p_mask; 
};

const std::string CELL_PENT_MASK_FILE = "cpm.data";
const std::string TASK_FILE = "task.data";

std::vector<
	std::vector<
		std::vector<field_t>
	>
> cell_to_pent_to_mask;

std::vector<
	std::vector<uint16_t>
> indicies;

std::map<std::string, field_t> task_set;

void init_cell_to_pent_to_mask() {
	std::ifstream ifs(CELL_PENT_MASK_FILE, std::ifstream::in);

	for (int c = 0; c < 64; ++c) {
		std::vector<
			std::vector<field_t>
		> pent_to_mask;
		for (int p = 0; p < 12; ++p) {
			uint32_t length = 0;
			ifs >> length;

			auto masks = std::vector<field_t>(length, 0);
			for (uint32_t i = 0; i < length; ++i) {
				ifs >> masks[i];
			}
			pent_to_mask.push_back(masks);
		}
		cell_to_pent_to_mask.push_back(pent_to_mask);
	}
	ifs.close();
}

void init_indicies() {
	const uint16_t TOTAL_PENTS = 12;
	for (uint16_t i = 0; i < (1 << TOTAL_PENTS); ++i) {
		std::vector<uint16_t> index;
		for (uint16_t j = 0; j < TOTAL_PENTS; ++j) {
			if (((i >> j) & 1) == 0) {
				index.push_back(j);
			}
		}
		indicies.push_back(index);
	}
}

void init_task_set() {
	std::ifstream ifs(TASK_FILE, std::ifstream::in);
	uint32_t length = 0;
	ifs >> length;

	std::string token;
	std::ifstream file(TASK_FILE, std::ifstream::in);
	while(std::getline(file, token)) {
	    std::istringstream line(token);
	    std::string arg = "";
		line >> arg;
		uint64_t val = 0;
		line >> val;
		task_set[arg] = val;
	}
}

void init() {
	init_cell_to_pent_to_mask();
	init_indicies();
	init_task_set();
}

bool bruteforce(
		uint8_t current_cell,
		field_t mask,
		pent_set_t taken, 
		std::vector<pentamino>& tessellation) {
	if (current_cell == 64) {
		return true;
	}
	if ((mask & (1ULL << current_cell)) != 0) {
		return bruteforce(current_cell + 1, mask, taken, tessellation);
	}
	auto const& index = indicies[taken];
	auto const& pent_to_mask = cell_to_pent_to_mask[current_cell];
	for (uint16_t i: index) {
		auto const& submasks = pent_to_mask[i];
		for (auto submask: submasks) {
			if ((submask & mask) != 0) {
				continue;
			}
			if (bruteforce(current_cell + 1, mask | submask, taken | (1 << i), tessellation)) {
				pentamino p = {
					.p_id = i,
					.p_mask = submask
				};
				tessellation.push_back(p);
				return true;
			}
		}
	}
	return false;
}

void solve(std::string const& task) {
	auto task_val = task_set[task];
	std::vector<pentamino> tessellation;
	bool result = bruteforce(0, task_val, 0, tessellation);
	if (not result) {
		std::cout << task << " " << task_val << " failed\n";
		return;
	}
	std::cout << task << " " << task_val << " ";
	for (auto t: tessellation) {
		std::cout << t.p_id << " " << t.p_mask << " ";
	}
	std::cout << "\n";
}

int main() {
	init();
	for (const auto& kv : task_set) {
	    solve(kv.first);
	}
	return 0;
}
