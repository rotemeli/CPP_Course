#ifndef EX02_CPP_CELL_H
#define EX02_CPP_CELL_H

/**
 * In this class I used the rule of zero because we didn't need to allocate memory on the heap
 * That is, we don't need a destructor and the default copy constructor and the = operator is fine
 * in terms of my implementation.
 */
class Cell {
private:
    char value;
    bool red_flag;
    bool blue_flag;

public:
    /**
     * Create an empty cell
     */
    Cell();

    /**
     * return cell value
     * @return
     */
    char getValue() const;

    /**
     * set cell value
     * @param value
     */
    void setValue(char value);

    /**
     * return if red flag is true
     * @return boolean
     */
    bool isRedFlag() const;

    /**
     * set red flag to true / false
     * @param redFlag
     */
    void setRedFlag(bool redFlag);

    /**
     * return if blue flag is true
     * @return boolean
     */
    bool isBlueFlag() const;

    /**
     * set blue flag to true / false
     * @param blueFlag
     */
    void setBlueFlag(bool blueFlag);
};


#endif //EX02_CPP_CELL_H
