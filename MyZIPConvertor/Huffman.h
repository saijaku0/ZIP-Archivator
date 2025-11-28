#pragma once
#include <memory>
#include <queue>
#include <vector>
#include <map>
#include <array>

using Frequencies = std::array<long long, 256>;
using CodeTable = std::map<unsigned char, std::vector<bool>>;

struct HuffmanNode {
	unsigned char byte_value = 0;
	long long frequency = 0;

	std::shared_ptr<HuffmanNode> left = nullptr;
	std::shared_ptr<HuffmanNode> right = nullptr;

	HuffmanNode(unsigned char byte, long long freq)
		: byte_value(byte), frequency(freq) { }

	HuffmanNode(std::shared_ptr<HuffmanNode> l, std::shared_ptr<HuffmanNode> r)
		: frequency(l->frequency + r->frequency), left(l), right(r) { }

	bool is_leaf() const {
		return left == nullptr && right == nullptr;
	}
};

struct CompareNodes {
	bool operator()(
		const std::shared_ptr<HuffmanNode>& a, 
		const std::shared_ptr<HuffmanNode>& b
	) const {
		return a->frequency > b->frequency;
	}
};

using MinPriorityQueue = std::priority_queue<
	std::shared_ptr<HuffmanNode>,
	std::vector<std::shared_ptr<HuffmanNode>>,
	CompareNodes
>;

class Huffman {
	std::shared_ptr<HuffmanNode> root_ = nullptr;
public:
	std::shared_ptr<HuffmanNode> build_tree(const Frequencies& frequencies);
	std::shared_ptr<HuffmanNode> get_root() const;
	CodeTable generate_codes();
private:
	void generate_codes_recursive(
		const std::shared_ptr<HuffmanNode>& node,
		std::vector<bool>& current_node,
		CodeTable& table
	);
};

