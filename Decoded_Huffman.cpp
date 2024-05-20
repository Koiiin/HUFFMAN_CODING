#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

string Decoding_pass[10];

// Node cấu trúc cho cây Huffman
struct Node {
    char ch;
    Node* left;
    Node* right;
    Node (char ch = '\0') : ch(ch), left(nullptr), right(nullptr) {}
};

// Hàm tạo Node mới
Node* getNode(char ch, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->left = left;
    node->right = right;
    return node;
}

// Hàm xây dựng cây Huffman từ bảng mã
Node* buildHuffmanTree(Node* root, const string& huffmanCode, char data) {
    Node* current = root;
    for (char bit : huffmanCode) {
        if (bit == '0') {
            if (!current->left) {
                current->left = getNode('\0', nullptr, nullptr);
            }
            current = current->left;
        } else { // bit == '1'
            if (!current->right) {
                current->right = getNode('\0', nullptr, nullptr);
            }
            current = current->right;
        }
    }
    current->ch = data;
    return root;
}

// Hàm giải mã chuỗi nhị phân dựa trên cây Huffman
string decodeHuffman(Node* root, const string& binaryStr) {
    string decodedStr = "";
    Node* current = root;

    for (char bit : binaryStr) {
        if (bit == '0') {
            current = current->left;
        } else { // bit == '1'
            current = current->right;
        }

        if (!current->left && !current->right) {
            decodedStr += current->ch;
            current = root;
        }
    }

    return decodedStr;
}

int main() {

    string HEAD_decoded = "DATA_Decoded_";
    string TAIL_decoded = ".txt";

    string HEAD_encoded = "DATA_Encoded_";
    string TAIL_encoded = ".txt";

    string HEAD_frequency_table = "DATA_Frequency_table_";
    string TAIL_fequency_table = ".txt";


    for (int k = 1; k <= 10; ++k) {
        string BODY = to_string(k);
        string file_decoded = HEAD_decoded + BODY + TAIL_decoded;
        string file_encoded = HEAD_encoded + BODY + TAIL_encoded;
        string file_fequency_table = HEAD_frequency_table + BODY + TAIL_fequency_table;

        // Đọc chuỗi nhị phân đã mã hóa từ file
        ifstream encodedFile(file_encoded);
        string encodedStr;
        encodedFile >> encodedStr;
        encodedFile.close();

        // Đọc bảng mã Huffman từ file
        ifstream huffmanFile(file_fequency_table);
        int n;
        huffmanFile >> n;
        huffmanFile.ignore();

        Node* root = new Node();
        while (n > 0) {
            string line;
            getline(huffmanFile, line);
            if (!line.empty()) {
                char data = line[0];
                string bit = line.substr(2);
                root = buildHuffmanTree(root, bit, data);
                n--;
            }
        }
        huffmanFile.close();

        // Giải mã chuỗi nhị phân
        string decodedStr = decodeHuffman(root, encodedStr);

        ofstream Decode(file_decoded);
        Decode << decodedStr;
        Decode.close();
    }

    return 0;
}
