#include "main.hpp"

template <typename T>
class List
{
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T &get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;

    virtual List<T> *subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0;
};

template <typename T>
class Feild : public List<T>
{
private:
    class Node
    {
    public:
        T pointer;
        Node *next;

    public:
        Node(T pointer, Node *next = nullptr) : pointer(pointer), next(next) {}
        //class Node là nơi lưu trữ từng ô của excel gồm pointer là điểm ảnh và next là Node tiếp theo
    };

private:
    Node *head; //Node đầu trong dslk đơn
    Node *tail; //Node cuối trong dslk đơn
    int size; //số lượng Node của dslk

public:
    //hàm khởi tạo 
    Feild()
    {
        head = tail = nullptr;
        size = 0;
    }
    //hàm hủy
    ~Feild()
    {
        this->clear();
    }
    //thêm node vào cuối dslk
    void push_back(T value){
        Node *newNode = new Node(value);
        //tạo một node mới được truyền vào tham số value
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    //thêm node vào đầu dslk
    void push_front(T value){
        Node *newNode = new Node(value); 
        if (head == NULL) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    //chèn node mới vào vị trí index, nếu index == size -> thêm vào cuối dslk
    void insert(int index, T value){
        if(index < 0 || index > size) return;
        Node *newNode = new Node(value);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
            if (size == 0){
                tail = newNode;
            }
        } else if (index == size) {
            tail->next = newNode;
            tail = newNode;
        } else {
            Node* tmp = head;
            for (int i = 0; i < index - 1; i++) {
                tmp = tmp->next;
            }
            newNode->next = tmp->next;
            tmp->next = newNode;
        }
        size++;
    }
    //xóa node tại vị trí index
    void remove(int index){
        if(index < 0 || index >= size) return;
        Node* removeNode;
        if (this->size == 1) {
            removeNode = head;
            head = tail = nullptr;
        } else if (index == 0) {
            removeNode = head;
            head = head->next;
        } else {
            Node* tmp = head;
            for (int i = 1; i < index; i++)
            tmp = tmp->next;
            removeNode = tmp->next;
            tmp->next = removeNode->next;
            if (index == this->size-1) tail = tmp;
        }
        delete removeNode;
        this->size--;
    }
    //truy xuất phần tử tại vị trí index
    T& get(int index) const{
        if(index < 0 || index >= this->size) {
            throw std::out_of_range("get(): Out of range");
        }
        Node* tmp = head;
        for (int i = 0; i < index; ++i){
            tmp = tmp->next;
        }
        return tmp->pointer;
    }
    //trả về kích thước của dslk
    int length() const
    {
        return size;
    }
    //xóa hết node trong dslk
    void clear(){
        while (head != NULL) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = NULL;
        size = 0;
    }
    //in các phần tử trong dslk
    void print() const
    {
        if (size == 0)
            cout << "nullptr";
        Node *temp = head;
        for (int i = 0; i < this->size; i++)
        {
            cout << temp->pointer;
            if (i != this->size - 1)
                cout << " ";
            temp = temp->next;
        }
    }
    //đảo ngược các phần tử trong dslk
    void reverse(){  
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        Node* curr = head;
        Node* prev = nullptr;
        Node* next = nullptr;
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        tail = head;
        head = prev;
    }
    //in từ phần tử start đến end
    void printStartToEnd(int start, int end) const
    {
        Node *temp = head;
        for (int i = 0; i < start; i++)
            temp = temp->next;
        for (int i = start; i < end && i < this->size; i++)
        {
            if (i == end - 1 || i == this->size - 1)
                cout << temp->pointer;
            else
                cout << temp->pointer << " ";
            temp = temp->next;
        }
    }
    //cắt dslk từ đoạn start đến end
    List<T>* subList(int start, int end){

        if(this->size <= start) return nullptr;
        List<T>* result = new Feild<T>();
        Node* curr = head;
        int index = 0;
        while (curr != nullptr && index < end) {
            if (index >= start) {
                result->push_back(curr->pointer);
            }
            curr = curr->next;
            index++;
        }
        return result;
    }
};

class Dataset
{
private:
    List<List<int> *> *data;
    List<string> *nameLabel;
    // You may need to define more
public:
    //hàm khởi tạo
    Dataset()
    {
        this->nameLabel = new Feild<string>();
        this->data = new Feild<List<int> *>();
    }
    //hàm hủy
    ~Dataset()
    {
        for (int i=0;i<data->length();i++){
        data->get(i)->clear();
      
        }
        for(int i = 0; i< data->length(); i++){
            delete this->data->get(i);
        }
        delete data;
        delete nameLabel;
    }
    //hàm sao chép
    Dataset(const Dataset& other)
    {
            this->nameLabel = new Feild<string>();
            for (int i = 0; i < other.nameLabel->length(); ++i){
                this->nameLabel->push_back(other.nameLabel->get(i));
            }
            
            this->data = new Feild<List<int>*>();
            int sohang = other.data->length();
            int socot = other.nameLabel->length();
            for (int i = 0; i < sohang; ++i){
            List<int>* newRow = new Feild<int>();
            for (int j = 0; j < socot; ++j){
                newRow->push_back(other.data->get(i)->get(j));
            }
            this->data->push_back(newRow);
        }
    }
    //hàm sao chép
    Dataset& operator=(const Dataset& other)
    {
        if (this != &other){
            delete data;
            delete nameLabel;
            this->nameLabel = new Feild<string>();
            for (int i = 0; i < other.nameLabel->length(); ++i){
                this->nameLabel->push_back(other.nameLabel->get(i));
            }

            this->data = new Feild<List<int>*>();
            int sohang = other.data->length();
            int socot = other.nameLabel->length();
            for (int i = 0; i < sohang; ++i){
            List<int>* newRow = new Feild<int>();
            for (int j = 0; j < socot; ++j){
                newRow->push_back(other.data->get(i)->get(j));
            }
            this->data->push_back(newRow);
            }
        }
        return *this;
    }

    List<List<int> *> *getData() const
    {
        return data;
    }

    bool loadFromCSV(const char *fileName) {
        ifstream input(fileName);
        if (!input.is_open()) {
            return false;
        }
        string hangduocdocvao;
        if (input >> hangduocdocvao) {
            for (int i = 0; i < hangduocdocvao.length(); i++) {
                if (hangduocdocvao[i] == ',') {
                    hangduocdocvao[i] = ' ';
                }
            }
            stringstream ss(hangduocdocvao);
            string columnName;
            while (ss >> columnName) {
                nameLabel->push_back(columnName);
            }
        }
        while (input >> hangduocdocvao) {
            for (int i = 0; i < hangduocdocvao.length(); i++) {
                if (hangduocdocvao[i] == ',') {
                    hangduocdocvao[i] = ' ';
                }
            }
            stringstream ss(hangduocdocvao);
            int dulieu;
            List<int> *tmp = new Feild<int>();
            while (ss >> dulieu) {
                tmp->push_back(dulieu);
            }
            data->push_back(tmp);
        }
        return true;
    }

    void getShape(int& nRows, int& nCols) const
    {
        nRows = data->length();
        nCols = data->get(0)->length();
    }

    void columns() const
    {
        nameLabel->printStartToEnd(0,nameLabel->length());
    }

    void printHead(int nRows = 5, int nCols = 5) const
    {
        if(nRows <= 0 || nCols <= 0) return;
        if (data->length() == 0) 
        {
            nameLabel->printStartToEnd(0, nCols);
            return;
        }
        int sohangcanin = min(nRows, data->length());
        int socotcanin = min(nCols, nameLabel->length());
        nameLabel->printStartToEnd(0, socotcanin);
            cout << endl;
        for (int i = 0; i < sohangcanin; ++i) {
            data->get(i)->printStartToEnd(0, socotcanin);
            if (i < sohangcanin - 1)
            cout << endl;
        }
    }
    
    void printTail(int nRows = 5, int nCols = 5) const
    {
        if (nRows <= 0 || nCols <= 0) 
        return;
        if (data->length() == 0){
        nameLabel->printStartToEnd(nameLabel->length()-min(nCols, nameLabel->length()), nameLabel->length());
        return;
        }
        int sohangcanin = min(nRows, data->length()); 
        int socotcanin = min(nCols, nameLabel->length()); 
        nameLabel->printStartToEnd(nameLabel->length() - socotcanin, nameLabel->length());
        cout << endl;
        for (int i = data->length() - sohangcanin; i < data->length(); ++i){
            data->get(i)->printStartToEnd(nameLabel->length() - socotcanin,nameLabel->length());
            if (i < data->length() - 1)
            cout << endl;
        }
    }

    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        if (axis == 0){
            if (index >= data->length() || index < 0) return false;
            data->remove(index);
            return true;
        } else if (axis == 1) {
            int vitricotcanxoa = -1;
            for (int i = 0; i < nameLabel->length(); ++i){
                if (nameLabel->get(i) == columns){
                    vitricotcanxoa = i;
                    break;
                }
            }
            if (vitricotcanxoa == -1) return false;
            for (int i = 0; i < data->length(); ++i){
                List<int>* row = data->get(i);
                row->remove(vitricotcanxoa);
            }
            nameLabel->remove(vitricotcanxoa);
            return true;
        } else {
            return false;
        }
    }

    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const {
        Dataset result;
        if (endRow == -1) {
            endRow = this->data->length();
        } 
        if (endCol == -1) {
            endCol = this->nameLabel->length();
        }
        if (startRow > endRow || startCol > endCol || endCol < -1 || endRow < -1)
            return result;
        
        if (startRow >= this->data->length() || startCol >= this->nameLabel->length()) {
        return result; 
        }
        if (this->data->length() == 0) {
            return result;
        }
        result.nameLabel = new Feild<string>();
        result.data = new Feild<List<int>*>();
        endRow = min(endRow, this->data->length() - 1); 
        endCol = min(endCol, this->nameLabel->length() - 1);
        for (int i = startCol; i <= endCol && i < this->nameLabel->length(); ++i) {
            result.nameLabel->push_back(nameLabel->get(i));
        }

        for (int i = startRow; i <= endRow && i < this->data->length(); ++i) {
            List<int>* hangsaochep = new Feild<int>();
            for (int j = startCol; j <= endCol && j < this->data->get(i)->length(); ++j) {
                hangsaochep->push_back(data->get(i)->get(j));
            }
            result.data->push_back(hangsaochep);
        }
        return result;
    }


    double distanceEuclidean(const List<int>* a, const List<int>* b) const{
    double distance = 0.0;
    int mangnganhon = min(a->length(), b->length());
    for (int i = 0; i < mangnganhon; ++i) {
        double diff = a->get(i) - b->get(i);
        distance += diff * diff;
    }
    if (a->length() != b->length()) {
        const List<int>* mangdaihon = (a->length() > b->length()) ? a : b;
        for (int i = mangnganhon; i < mangdaihon->length(); ++i) {
            double diff = mangdaihon->get(i);
            distance += diff * diff;
        }
    }
    
    return sqrt(distance);
    }

    Dataset predict(const Dataset &X_train, const Dataset &Y_train, const int k) const
    {
        Dataset result;
        if (k <= 0 || this->data->length() == 0 || X_train.data->length() == 0 || Y_train.data->length() == 0)
            return result;
        result.nameLabel->push_back(Y_train.nameLabel->get(0));
        int Kichthuoccuatrain = min(X_train.data->length(), Y_train.data->length());
        int *label = new int[Kichthuoccuatrain];
        double *distances = new double[Kichthuoccuatrain];
        for (int i = 0; i < this->data->length(); i++)
        {
            for (int j = 0; j < Kichthuoccuatrain; j++)
            {
                label[j] = Y_train.data->get(j)->get(0); 
                distances[j] = this->distanceEuclidean(this->data->get(i), X_train.data->get(j)); 
            }
            for (int j = 1; j < Kichthuoccuatrain; j++) {
                double key_distance = distances[j];
                int key_label = label[j];
                int l = j - 1;
                while (l >= 0 && distances[l] > key_distance) {
                    distances[l + 1] = distances[l];
                    label[l + 1] = label[l];
                    l--;
                }
                distances[l + 1] = key_distance;
                label[l + 1] = key_label;
            }
            int demsonhan[10] = {0}; 
            for (int j = 0; j < k; j++)
            {
                demsonhan[label[j]]++;
                if (j >= Kichthuoccuatrain) { 
                    throw std::out_of_range("get(): Out of range");
                }
            }
            int max_count = 0;
            int predicted_label = label[0];
            for (int j = 0; j < k; j++)
            {
                if (demsonhan[label[j]] > max_count || (demsonhan[label[j]] == max_count && label[j] < predicted_label) || (demsonhan[label[j]] == max_count && label[j] == predicted_label))
                {
                    max_count = demsonhan[label[j]];
                    predicted_label = label[j];
                }
            }
            List<int> *tmp = new Feild<int>();
            tmp->push_back(predicted_label);
            result.data->push_back(tmp);
        }
        delete[] distances;
        delete[] label;
        return result;
    }

    double score(const Dataset &y_predict) const
    {
        if (y_predict.data->length() == 0 || this->data->length() == 0)
        return -1;
        if (y_predict.data->length() != this->data->length())
            return -1;
        int dem = 0;
        int length = min(this->data->length(), y_predict.data->length());
        for (int i = 0; i < length; i++) {
        if (this->data->get(i)->get(0) == y_predict.data->get(i)->get(0)) {
            dem++;
            }
        }
        return static_cast<double>(dem) / y_predict.data->length();
    }
};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    // You may need to define more
public:
    kNN(int k = 5) : k(k){};
    void fit(const Dataset &X_train, const Dataset &y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset &X_test)
    {
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset &y_test, const Dataset &y_pred)
    {
        return y_test.score(y_pred);
    }
};
void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test);

// Please add more or modify as needed