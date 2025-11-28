#include "Huffman.h"

std::shared_ptr<HuffmanNode> Huffman::build_tree(const Frequencies& frequencies) {
	MinPriorityQueue pq;

	for (int i = 0; i < 256; i++)
		if (frequencies[i] > 0)
			pq.push(std::make_shared<HuffmanNode>(static_cast<unsigned char>(i), frequencies[i]));

    if (pq.empty()) {
        root_ = nullptr;
        return nullptr;
    }

    if (pq.size() == 1) {
        auto single_node = pq.top();
        pq.pop();
        root_ = std::make_shared<HuffmanNode>(single_node, std::make_shared<HuffmanNode>(0, 0));
    }
    else {
        while (pq.size() > 1) {
            auto left_child = pq.top(); pq.pop();
            auto right_child = pq.top(); pq.pop();

            auto parent = std::make_shared<HuffmanNode>(left_child, right_child);
            pq.push(parent);
        }
        root_ = pq.top();
    }

    return root_;
}

std::shared_ptr<HuffmanNode> Huffman::get_root() const {
    return root_;
}

CodeTable Huffman::generate_codes() {
	CodeTable table;
	std::vector<bool> current_code;

	if (!root_) return table;

	if (root_->is_leaf()) {
		current_code.push_back(false);
		table[root_->byte_value] = current_code;
	}
	else {
		generate_codes_recursive(root_, current_code, table);
	}

	return table;
}

//-----------------
// private function
//-----------------

void Huffman::generate_codes_recursive(
	const std::shared_ptr<HuffmanNode>& node,
	std::vector<bool>& current_node,
	CodeTable& table
) {
	if (!node) return;

	if (node->is_leaf()) {
		table[node->byte_value] = current_node;
		return;
	}

	current_node.push_back(false);
    generate_codes_recursive(node->left, current_node, table);
	current_node.pop_back();

	current_node.push_back(true);
    generate_codes_recursive(node->right, current_node, table);
	current_node.pop_back();
}