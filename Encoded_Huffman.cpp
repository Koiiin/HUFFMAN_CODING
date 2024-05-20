#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

string Encoding_pass[10];

// Định nghĩa cấu trúc nút Huffman
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Định nghĩa hàm so sánh cho priority_queue
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->frequency > r->frequency;
    }
};

// Tính tần suất ký tự
unordered_map<char, int> calculateFrequency(const string &data) {
    unordered_map<char, int> frequency;
    for (char ch : data) {
        frequency[ch]++;
    }
    return frequency;
}

// Tạo hàng đợi ưu tiên từ tần suất ký tự
priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> createPriorityQueue(const unordered_map<char, int>& frequency) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (const auto& pair : frequency) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    return pq;
}

// Xây dựng cây Huffman
HuffmanNode* buildHuffmanTree(priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare>& pq) {
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();
        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }
    return pq.top();
}

// Tạo mã Huffman
void generateHuffmanCodes(HuffmanNode* root, string str, std::unordered_map<char, string> &huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->data] = str.empty() ? "0" : str;  // Trường hợp chuỗi đầu vào chỉ có các ký tự giống nhau
    }

    generateHuffmanCodes(root->left, str + "0", huffmanCode);
    generateHuffmanCodes(root->right, str + "1", huffmanCode);
}

unordered_map<char, string> getHuffmanCodes(HuffmanNode* root) {
    unordered_map<char, string> huffmanCode;
    generateHuffmanCodes(root, "", huffmanCode);
    return huffmanCode;
}

// Mã hóa chuỗi đầu vào sử dụng mã Huffman
string encode(const string &data, const unordered_map<char, string> &huffmanCode) {
    string encodedString = "";
    for (char ch : data) {
        encodedString += huffmanCode.at(ch);
    }
    return encodedString;
}


// Hàm giải phóng bộ nhớ của cây Huffman
void freeHuffmanTree(HuffmanNode* root) {
    if (root == nullptr) return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}

int main() {

    string HEAD_input = "DATA_INPUT_";
    string TAIL_input = ".txt";

    string HEAD_encoded = "DATA_Encoded_";
    string TAIL_encoded = ".txt";

    string HEAD_frequency_table = "DATA_Frequency_table_";
    string TAIL_fequency_table = ".txt";
    

    for (int k = 1; k <= 10; ++k)
    {
        string BODY = to_string(k);
        // Tạo tên file đầu vào và đầu ra
        string file_input   = HEAD_input   + BODY + TAIL_input;
        string file_encoded = HEAD_encoded + BODY + TAIL_encoded;
        string file_frequency = HEAD_frequency_table + BODY + TAIL_fequency_table;
       
        // Đọc dữ liệu từ file đầu vào
        ifstream Input(file_input);
        

        Input >> Encoding_pass[k-1];

        // Lấy dữ liệu đầu vào
        string text = {Encoding_pass[k-1]};


        // Tính tần suất ký tự
        unordered_map<char, int> frequency = calculateFrequency(text);

        // Tạo hàng đợi ưu tiên
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq = createPriorityQueue(frequency);

        // Xây dựng cây Huffman
        HuffmanNode* root = buildHuffmanTree(pq);

        // Tạo mã Huffman
        unordered_map<char, string> huffmanCode = getHuffmanCodes(root);

        // Mã hóa chuỗi đầu vào
        string encodedString = encode(text, huffmanCode);
                

        // Ghi dữ liệu vào file đầu ra
        ofstream Output(file_encoded);
        // Kiểm tra xem file có mở được không
        if (Output.is_open()) {
            // Viết vào file
            Output << encodedString;
            // Đóng file
            Output.close();
        }


        ofstream Freq(file_frequency);

        if (Freq.is_open()) {
            int i = huffmanCode.size();
            Freq << i << '\n';

            for (auto pair : huffmanCode) {
                Freq << pair.first << " " << pair.second << '\n';
            }
            Freq.close();
        }

        // Giải phóng bộ nhớ của cây Huffman
        freeHuffmanTree(root);
    }

    

    return 0;
}
