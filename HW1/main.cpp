#include <iostream>
#include <sstream>
#include <cstring>


typedef struct Observation {
    /*
     * Make observation struct
     */
    std::string name;
    double* vec_arr{};
    int place = 0;
} Observation;


Observation* obCreate(int dim) {
    /*
     * Make observation object
     */
    auto* ob = new Observation;
    ob->vec_arr = new double[dim];
    return ob;
}


void obDestroy(Observation* ob) {
    /*
     * Free all the initialized memory
     */
    delete[] ob->vec_arr;
    delete ob;
}


bool ob_is_in(Observation obs[], int length, const std::string& name) {
    /*
     * Check if given observation is in the Observations array
     * return true if the given observation is in, otherwise false
     */
    for(int i = 0; i < length; i++) {
        if(obs[i].name == name) {
            return true;
        }
    }
    return false;
}


Observation given_ob(Observation obs[], int length, const std::string& name) {
    /*
     * return Observation by the given name
     */
    for(int i = 0; i < length; i++) {
        if(obs[i].name == name) {
            return obs[i];
        }
    }
}


bool is_empty(int size) {
    /*
     * Check if there is observation in the array
     */
    if(size == 0) {
        std::cerr << "Empty calculator." << std::endl;
        return true;
    }
    return false;
}

double* arr_ret(std::string& s, int dim) {
    /*
     * A function that gets a string of doubles separated by spaces,
     * Split the doubles by spaces and set them in doubles array.
     * The array presents single observation vector values.
     */
    int count = 0;
    for(char i : s) {
        if(i == ' ') {
            count++;
        }
    }
    if(count != dim - 1) {
        return nullptr;
    }

    auto* arr = new double[dim];
    std::fill(arr, arr + dim, NULL);
    int i = 0;
    std::string delimiter = " ";
    size_t pos;
    std::string token;
    double num;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        std::stringstream ss;
        token = s.substr(0, pos);
        ss << token;
        ss >> num;
        arr[i] = num;
        i++;
        s.erase(0, pos + delimiter.length());
    }
    std::stringstream sst;
    sst << s;
    sst >> num;
    arr[i] = num;
    return arr;
}

Observation* reSize(Observation obs[], int length, int maxSize, int &start_size) {
    /*
     * Function that resize the memory when the observation array is full.
     */
    Observation *tmp;
    if(length*2 >= maxSize) {
        tmp = new Observation[maxSize];
        start_size = maxSize;
    }
    else {
        tmp = new Observation[length * 2];
        start_size = length*2;
    }
    std::copy(obs, obs + length, tmp);

    for(int i = 0; i < length; i++) {
        obDestroy(&obs[i]);
    }
    delete[] obs;

    return tmp;
}


void init(const int maxSize, const int dim) {
    /*
     * Start the calculator and handle all the cases [1-5]
     */
    std::string str;
    int index = 0;
    bool flag = false;
    int start_size = 50;
    auto* observations = new Observation[start_size];

    float mean[dim];
    float cov_mat[dim][dim];

    std::cout << "[1] New observation\n[2] Print observation\n[3] Expected value vector\n"
                 "[4] Covariance matrix\n[5] Exit" << std::endl;

    while(true) {
        getline(std::cin, str);                 // Get operation from the user
        if(str == "5") {
            /*
             * Destroy all the memory and exit.
             */
            for(int i = 0; i < index; i++) {
                obDestroy(&observations[i]);
            }
            delete[] observations;
            exit(0);
        }

        else if(str == "1") {
            /*
             * get the name, vector values from the user and set them in new observation.
             */
            std::string ob_name;
            Observation* ob = obCreate(dim);
            std::cout << "Enter observation name:" << std::endl;
            std::getline(std::cin, ob_name);
            if(!ob_is_in(observations, dim, ob_name)) {
                ob->name = ob_name;
            }
            else {
                *ob = given_ob(observations, dim, ob_name);
                flag = true;
            }
            std::string values;
            std::cout << "Enter observation values:" << std::endl;
            getline(std::cin, values);
            ob->vec_arr =  arr_ret(values, dim);

            if(ob->vec_arr == nullptr) {
                /*
                 * Checks if the user has entered an exact number of values to the vector
                 */
                std::cerr << "Invalid observation." << std::endl;
                continue;
            }

            if(flag) {
                observations[ob->place] = *ob;
                continue;
            }
            observations[index] = *ob;
            ob->place = index;
            index++;
            if(index == start_size) {
                observations = reSize(observations, index, maxSize, start_size);
            }
        }

        else if(str == "2") {
            /*
             * Prints the observation according to the name given by the user
             */
            std::string name;
            std::cout << "Enter observation name:" << std::endl;
            getline(std::cin, name);
            if(ob_is_in(observations, index, name)){
                Observation o = given_ob(observations, index, name);
                std::cout << o.name << " = [ ";
                for(int  i = 0; i < dim; i++) {
                    std::cout << o.vec_arr[i];
                    if(i != dim-1) {
                        std::cout << " ";
                    }
                }
                std::cout << "]" << std::endl;
            }
            else {
                std::cerr << "Invalid or nonexistent observation." << std::endl;
            }
        }

        else if(str == "3") {
            /*
             * Calculate the mean vector and prints it.
             */
            if(is_empty(index)) {
                continue;
            }
            for(int i = 0; i < dim; i++) {
                float avg = 0;
                for(int j = 0; j < index; j++) {
                    avg += (float)observations[j].vec_arr[i];
                }
                mean[i] = avg / (float)index;
            }
            std::cout << "mean = [ ";
            for(int i = 0; i < dim; i++) {
                std::cout << mean[i];
                if(i != dim-1) {
                    std::cout << " ";
                }
            }
            std::cout << "]" << std::endl;
        }

        else if(str == "4") {
            /*
             * Calculate the covariance matrix and prints it.
             */
            if(is_empty(index)) {
                continue;
            }

            for(int i = 0; i < dim; i++) {
                float avg = 0;
                for(int j = 0; j < index; j++) {
                    avg += (float)observations[j].vec_arr[i];
                }
                mean[i] = avg / (float)index;
            }
            for(int i = 0; i < dim; i++) {
                if(i != dim-1) {
                }
            }

            std::cout << "cov = [" << std::endl;
            for(int i = 0; i < dim; i++) {
                for(int j = 0; j < dim; j++) {
                    float mat_val = 0;
                    for(int k = 0; k < index; k++) {
                        mat_val += (float)((observations[k].vec_arr[i] - mean[i]) * (observations[k].vec_arr[j] - mean[i]));
                    }
                    if(index > 1) {
                        cov_mat[i][j] = mat_val / ((float)index - 1);
                        std::cout << " " << cov_mat[i][j];
                    }
                    else if(index == 1) {
                        cov_mat[i][j] = mat_val;
                        std::cout << " " << cov_mat[i][j];
                    }
                }
                std::cout << "\n";
            }
            std::cout << "]" << std::endl;
        }

        else {
            std::cerr << "Invalid option." << std::endl;
        }
    }
}


int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cerr << "Invalid arguments <int> <int>." << std::endl;
        exit(-1);
    }

    int dim = std::stoi(argv[1]);       // Converts the value from a string to an integer
    int size = std::stoi(argv[2]);      // Converts the value from a string to an integer

    init(size, dim);

    return 0;
}
