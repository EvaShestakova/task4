#include "func.h"

ifstream::pos_type getsize(const string& fn) {
    ifstream file(fn, ifstream::ate);
    return file.tellg();
}

void readfile(const string& fl, vector<int>& freq) {
    int flsize = getsize(fl);
    if (flsize < 0) {
        throw - 1;
    }
    ifstream file(fl, ifstream::binary);
    if (!file) {
        throw - 2;
    }

    int i = 0;
    cout << "Reading file... " << fl  << endl;
    while (true) {
        char ch;
        file.read(&ch, 1);

        if (file.eof()) {
            break;
        }

        // if (static_cast<unsigned char>(ch) != 13) {
        freq[static_cast<unsigned char>(ch)]++;
        //}

        i++;
    }



    /* for (unsigned int i = 0; i < freq.size(); i++) {
         if (freq[i] != 0) {
             cout << "[" << i << "] = " << freq[i] << ", \t";
         }
     }
     cout << endl;*/
    file.close();
}

void makecode(Node::pointer& node, string str, vector<string>& codes) {
    if (node->left != nullptr) {
        makecode(node->left, str + "0", codes);
    }
    if (node->right != nullptr) {
        makecode(node->right, str + "1", codes);
    }
    if (node->left == nullptr && node->right == nullptr) {
        node->code(str);
        codes[node->getbyte()] = str;
        // cout << "leaf: " << *node << " code: " << node->code() << "\n";
    }
}

void fillqueue(vector<int>& freq, queue_t& queue) {
    for (unsigned int i = 0; i < freq.size(); i++) { //unsigned
        if (freq[i] != 0) {
            Node::pointer node = make_shared<Node>(i, freq[i]);
            queue.push(node);
        }
    }
}

void buildtree(queue_t& queue) {
    while (queue.size() > 1) {
        Node::pointer x = queue.top();
        queue.pop();
        Node::pointer y = queue.top();
        queue.pop();
        string name = x->getname() + y->getname();
        Node::pointer z = make_shared<Node>(name, x->getfreq() + y->getfreq());
        z->left = x;
        z->right = y;
        x->parent = z;
        y->parent = z;
        queue.push(z);
    }
}

string message2code(const string& filename, const vector<string>& codes) {
    string msg{ "" };
    ifstream ifs(filename, ifstream::binary);
    if (!ifs) {
        throw - 3;
    }
    while (true) {
        char ch;
        ifs.read(&ch, 1);

        if (ifs.eof()) {
            break;
        }

        msg += codes[static_cast<uchar>(ch)];
    }
    return msg;
}
void writefile(const string& filename, vector<int>& freq, const queue_t& queue, const string& message) {
    string new_filename = filename + ".hff";
    ofstream ofs(new_filename, ofstream::binary);
    if (!ofs) {
        throw - 4;
    }
    uchar count = count_if(freq.begin(), freq.end(), [](const int& value) {return (value != 0); });//количество ненулевых символов
    ofs.write(reinterpret_cast<char*>(&count), sizeof count);
    for_each(freq.begin(), freq.end(), [index = uchar(0), &ofs](int& value) mutable{
        if (value != 0) {
            ofs.write(reinterpret_cast<char*>(&index), sizeof index);
            ofs.write(reinterpret_cast<char*>(&value), sizeof value); //int 4 байта
        }
        ++index;
    });
    int byte_count = message.size() / CHAR_BIT; //char_bit=8
    uchar modulo = message.size() % CHAR_BIT;
    // cout << "byte count: " << byte_count << " of size " << message.size()<<"\n";
    // cout << "modulo: " << (int)modulo << " of size " << message.size() << "\n";
    ofs.write(reinterpret_cast<char*>(&byte_count), sizeof byte_count);
    ofs.write(reinterpret_cast<char*>(&modulo), sizeof modulo);
    int i = 0;
    for (; i < byte_count; ++i) {
        bitset<CHAR_BIT> b(message.substr(i * CHAR_BIT, CHAR_BIT));
        uchar value = static_cast<uchar>(b.to_ulong());
        ofs.write(reinterpret_cast<char*>(&value), sizeof value);
    }
    if (modulo > 0) {
        bitset<CHAR_BIT> b(message.substr(i * CHAR_BIT, modulo));
        uchar value = static_cast<uchar>(b.to_ulong());
        ofs.write(reinterpret_cast<char*>(&value), sizeof value);
    }
}

void read_decoding_file(string& filename, vector<int>& freq, string& message) {
    string new_filename = filename + ".hff";
    ifstream ifs(new_filename, ifstream::binary);
    if (!ifs) {
        throw - 4;
    }
    uchar count = 0;
    ifs.read(reinterpret_cast<char*>(&count), sizeof count);
    //cout << "New count: " << (int)count<<  "\n";

    int i = 0;
    while (i < count) {
        uchar ch;
        ifs.read(reinterpret_cast<char*>(&ch), sizeof ch);
        int f = 0;
        ifs.read(reinterpret_cast<char*>(&f), sizeof f);
        freq[ch] = f;
        i++;
    }

    /*for_each(freq.begin(), freq.end(), [index = uchar(0)](const int& value) mutable{
        if (value != 0) {
            cout << "[" << static_cast<char>(index) << "] = " << value << "\n";
        }
        ++index;
    });*/
    int byte_count = 0;
    uchar modulo = 0;
    ifs.read(reinterpret_cast<char*>(&byte_count), sizeof byte_count);
    ifs.read(reinterpret_cast<char*>(&modulo), sizeof modulo);
    //cout << "New byte_count: " << (int)byte_count << "\n";
    //cout << "New modulo: " << (int)modulo << "\n";

    i = 0;
    for (; i < byte_count; ++i) {
        uchar byte;
        ifs.read(reinterpret_cast<char*>(&byte), sizeof byte);
        bitset<CHAR_BIT> b(byte);
        message += b.to_string();
    }
    if (modulo > 0) {
        uchar byte;
        ifs.read(reinterpret_cast<char*>(&byte), sizeof byte);
        bitset<CHAR_BIT> b(byte);
        message += b.to_string().substr(CHAR_BIT - modulo, CHAR_BIT);
    }
    // cout << message << endl;
}

void make_char(const Node::pointer& root, const string& message, const string& filename) {
    Node::pointer node = root;
    string new_filename = filename + ".1";
    ofstream ofs(new_filename, ofstream::binary);
    if (!ofs) {
        throw - 5;
    }
   // string t = "";
    for (size_t i = 0; i < message.size(); i++) {
        char ch = message[i];
        if (ch == '0') {
            if (node->left != nullptr) {
                node = node->left;
                if (node->isleaf()) {
                    //t= node->getbyte();
                    //ofs << t;
                    ofs << node->getbyte();
                    node = root;
                }
            }
        }
        else if (ch == '1') {
            if (node->right != nullptr) {
                node = node->right;
                if (node->isleaf()) {
                  //  t = node->getbyte();
                    //ofs << t;
                    ofs << node->getbyte();
                    node = root;
                }
            }
        }
    }
    // cout << "Text: [" << text << "]"<<endl;
}

void write_decoding_file(const string& filename, const string& text) {
    string new_filename = filename + ".1";
    ofstream ofs(new_filename, ofstream::binary);
    if (!ofs) {
        throw - 5;
    }
    ofs << text;
}

void zip(const string& filename) {
    vector<int> freq(256, 0); 
    readfile(filename, freq);

    queue_t queue;

    fillqueue(freq, queue);
    buildtree(queue);

    /* while (!queue.empty()) {
         cout << *(queue.top()) << " ";
         queue.pop();
     }*/

    vector<string> codes(256, "");
    Node::pointer root = queue.top();
    makecode(root, "", codes);

    string message = message2code(filename, codes);
    //cout << message << endl;

    writefile(filename, freq, queue, message);
}

void unzip(string& filename) {
    vector<int> freq2(256, 0);
    string message2 = "";

    read_decoding_file(filename, freq2, message2);

    queue_t queue2;
    fillqueue(freq2, queue2);
    buildtree(queue2);

    Node::pointer root2 = queue2.top();
    make_char(root2, message2, filename);

}