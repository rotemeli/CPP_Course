#ifndef EX03_CPP_VIRUS_H
#define EX03_CPP_VIRUS_H

#include <iostream>
#include <string>

class Virus {
private:
    std::string name;
    int* values;
    double approximation;
    int dim;
    int version;
    int counter;
    int* id;
    int Pm;
    std::string type;

public:
    /**
     * Creates a virus by given name and an array of integers
     * @param name
     * @param values
     */
    Virus(std::string name, int* values);

    /*
     * Big five
     */
    Virus(const Virus& other);

    Virus& operator=(const Virus& other);

    virtual ~Virus();

    Virus(Virus&& other) noexcept;

    Virus& operator=(Virus&& other) noexcept;

    /**
     * Swap two indexes in the array of the virus
     */
    void operator*();

    /**
     * Returns the name of the virus
     * @return
     */
    const std::string &getName() const;

    /**
     * Returns a pointer to the array of the virus
     * @return
     */
    int *getValues() const;

    /**
     * Returns the virus error from the target virus
     * @return
     */
    double getApproximation() const;

    /**
     * Return the version of the virus
     * @return
     */
    int getVersion() const;

    /**
     * Return the dim of the array
     * @return
     */
    int getDim() const;

    /**
     * Returns the version of the last created virus
     * @return
     */
    int *getId() const;

    /**
     * Returns the pm of the object
     * @return
     */
    int getPm() const;

    /**
     * Returns the virus type
     * @return
     */
    const std::string &getType() const;

    /**
     * Set the virus type
     * @param type
     */
    void setType(const std::string &type);

    /**
     * Set the array
     * @param values
     */
    void setValues(int *values);

    /**
     * Set the error
     * @param approximation
     */
    void setApproximation(double approximation);

    /**
     * Update the current version
     * @param version
     */
    void setVersion(int version);

    /**
     * Set the Pm value
     * @param pm
     */
    void setPm(int pm);

    /**
     * Increment by 1 the version of all viruses in one
     */
    void incrementId();

    /**
     * Calculates the error from the target virus
     * @return
     */
    double approximationCalc() const;

    /**
     * Binary operands for sorting
     * @param v
     * @return
     */
    bool operator>(const Virus& v) const;

    bool operator<=(const Virus& v) const;

    /**
     * Print operator
     * @param out
     * @param v
     * @return
     */
    friend std::ostream& operator<<(std::ostream& out, const Virus& v);
};


#endif //EX03_CPP_VIRUS_H
