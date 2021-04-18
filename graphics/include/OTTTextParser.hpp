#ifndef OTT_TEXT_PARSER_HPP
#define OTT_TEXT_PARSER_HPP

#include <vector>
#include <string>
#include <map>

namespace ott {
	/** Return true if an input string is numerical
	  */
	bool isNumeric(const std::string& str);

	/** Return true if an input string is numerical and is an integer
	  */
	bool isInteger(const std::string& str);

	/** Return true if an input string is numerical and is a decimal value
	  */
	bool isDecimal(const std::string& str);

	/** Return true if an input string is numerical and is a hexadecimal value
	  */
	bool isHexadecimal(const std::string& str);

	/** Return true if an input string is numerical and is a binary value
	  */
	bool isBinary(const std::string& str);

	/** Return true if an input string is NOT numerical
	  */
	bool isNotNumeric(const std::string& str);

	/** Compute the two's compliment of an unsigned byte
	  */
	short twosComp(const unsigned char& n);

	/** Split an input string into parts about a specified delimiter character
	  * @param input Input string to split into parts
	  * @param output Vector of strings to store split strings
	  * @param delim Delimiter character about which the input string will be split
	  * @return The number of output strings the input was split into
	  */
	unsigned int splitString(const std::string& input, std::vector<std::string>& output, const unsigned char& delim = '\t');

	/** Extract a sub-string from an input string
	  */
	std::string extractString(std::string& str, const char& c1, const char& c2, const std::string& repstr = "");

	/** Counter the number of occurances of character 'c' in the input string and return the result
	  */
	unsigned int countOccurances(const std::string& str, const char& c);

	/** Convert input integer to a hexadecimal string
	  */
	std::string getHex(const unsigned char& input);

	/** Convert input integer to a hexadecimal string
	  */
	std::string getHex(const unsigned short& input);

	/** Convert input integer to a binary string
	  */
	std::string getBinary(const unsigned char& input, const int& startBit = 0);

	/** Convert input integer to a binary string
	  */
	std::string getBinary(const unsigned short& input, const int& startBit = 0);

	/** Convert input integer to ascii string
	  */
	std::string getAscii(const unsigned short& input);

	/** Convert input integer to ascii string
	  */
	std::string getAscii(const unsigned int& input);

	/** Convert input integer to a decimal string
	  */
	std::string ucharToStr(const unsigned char& input);

	/** Convert input integer to a decimal string
	  */
	std::string ushortToStr(const unsigned short& input);

	/** Convert input integer to a decimal string
	  */
	std::string uintToStr(const unsigned int& input);

	/** Convert input floating point to a string
	  * If parameter 'fixed' is specified, fixed decimal point will be used
	  */
	std::string floatToStr(const float& input, const unsigned short& fixed = 0);

	/** Convert input double to a string
	  * If parameter 'fixed' is specified, fixed decimal point will be used
	  */
	std::string doubleToStr(const double& input, const unsigned short& fixed = 0);

	/** Convert input alpha-numerical string to uppercase
	  */
	std::string toUppercase(const std::string& str);

	/** Convert input alpha-numerical string to lowercase
	  */
	std::string toLowercase(const std::string& str);

	/** Strip trailing whitespace characters from an input string
	  */
	std::string stripWhitespace(const std::string& str);

	/** Strip ALL whitespace characters from an input string
	  */
	std::string stripAllWhitespace(const std::string& str);

	/** Remove the first occurance of a specified character from an input string
	  * @return True if a character was removed from the input string
	  */
	bool removeCharacter(std::string& str, const char& c);

	/** Remove ALL occurances of a specified character from an input string
	  * @return True if at least one character was removed from the input string
	  */
	bool removeAllCharacters(std::string& str, const char& c);

	/** Get an unsigned 8-bit integer from a user input string
	  * Acceptable input formats are decimal, hexadecimal, and binary (e.g. 1234, $abcd, and b0110)
	  * @return The integer converted from the input string or 0 in the event that the input string was not numerical
	  */
	unsigned char getUserInputUChar(const std::string& str);

	/** Get an unsigned 16-bit integer from a user input string
	  * Acceptable input formats are decimal, hexadecimal, and binary (e.g. 1234, $abcd, and b0110)
	  * @return The integer converted from the input string or 0 in the event that the input string was not numerical
	  */
	unsigned short getUserInputUShort(const std::string& str);

	/** Get an unsigned 32-bit integer from a user input string
	  * Acceptable input formats are decimal, hexadecimal, and binary (e.g. 1234, $abcd, and b0110)
	  * @return The integer converted from the input string or 0 in the event that the input string was not numerical
	  */
	unsigned int getUserInputUInt(const std::string& str);

	/** Concatenate two 8-bit integers into an 16-bit integer and return the result
	  * @param h Most significant 8-bits
	  * @param l Least significant 8-bits
	  * @return The resulting 16-bit integer, u16 = (h << 8) + l
	  */
	unsigned short getUShort(const unsigned char& h, const unsigned char& l);

	/** Get the state of a bit in an input 8-bit integer
	  * Parameter 'bit' expected to be in range [0, 7], but no checks are performed
	  */
	bool bitTest(const unsigned char& input, const unsigned char& bit);

	/** Get the state of a bit in an input 16-bit integer
	  * Parameter 'bit' expected to be in range [0, 15], but no checks are performed
	  */
	bool bitTest(const unsigned short& input, const unsigned char& bit);

	/** Get the state of a bit in an input 32-bit integer
	  * Parameter 'bit' expected to be in range [0, 31], but no checks are performed
	  */
	bool bitTest(const unsigned int& input, const unsigned char& bit);

	/** Set a bit of an input 8-bit integer
	  * Parameter 'bit' expected to be in range [0, 7], but no checks are performed
	  */
	void bitSet(unsigned char& input, const unsigned char& bit);

	/** Set a bit of an input 16-bit integer
	  * Parameter 'bit' expected to be in range [0, 15], but no checks are performed
	  */
	void bitSet(unsigned short& input, const unsigned char& bit);

	/** Set a bit of an input 32-bit integer
	  * Parameter 'bit' expected to be in range [0, 31], but no checks are performed
	  */
	void bitSet(unsigned int& input, const unsigned char& bit);

	/** Reset a bit of an input 8-bit integer
	  * Parameter 'bit' expected to be in range [0, 7], but no checks are performed
	  */
	void bitReset(unsigned char& input, const unsigned char& bit);

	/** Reset a bit of an input 16-bit integer
	  * Parameter 'bit' expected to be in range [0, 15], but no checks are performed
	  */
	void bitReset(unsigned short& input, const unsigned char& bit);

	/** Reset a bit of an input 32-bit integer
	  * Parameter 'bit' expected to be in range [0, 31], but no checks are performed
	  */
	void bitReset(unsigned int& input, const unsigned char& bit);

	/** Get an 8-bit mask for bits set between 'low' and 'high' (inclusive)
	  */
	unsigned char getBitmask(const unsigned char& low, const unsigned char& high);
}

enum class OPERATOR {
	NONE, 
	MULTIPLY, 
	DIVIDE, 
	MODULUS, 
	ADD, 
	SUBTRACT,
	BITSHIFT_LEFT, 
	BITSHIFT_RIGHT,
	BITWISE_AND, 
	BITWISE_XOR, 
	BITWISE_OR, 
	ASSIGNMENT,
	LESS_THAN, 
	GREATER_THAN, 
	LESS_THAN_EQUAL, 
	GREATER_THAN_EQUAL,
	EQUALITY, 
	NOT_EQUAL, 
	LOGICAL_AND, 
	LOGICAL_OR
};

enum class OPERATION { 
	NONE, 
	ARITHMETIC, 
	LOGICAL, 
	ASSIGNMENT 
};

enum class NUMTYPE { 
	NONE, 
	BOOLEAN, 
	INTEGER 
};

enum class CPPTYPE { 
	NONE, 
	BOOL, 
	UINT8, 
	UINT16, 
	UINT32, 
	INT8, 
	INT16, 
	INT32, 
	FLOAT 
};

class OperatorType {
public:
	std::string sName; ///< The string representing the mathematical operator

	OPERATOR op; ///< The type of mathematical operator

	OPERATION type; ///< The type of operation performed

	NUMTYPE operands; ///< The required operand type

	NUMTYPE result; ///< The output type of the performed operation

	/** Default constructor.
	*/
	OperatorType() :
		sName(),
		op(OPERATOR::NONE),
		type(OPERATION::NONE),
		operands(NUMTYPE::INTEGER),
		result(NUMTYPE::INTEGER)
	{
	}

	/** Operator constructor.
	* @param s The string representing the mathematical operator
	* @param op_ The type of mathematical operator
	* @param type_ The type of operation performed
	*/
	OperatorType(const std::string& s, const OPERATOR& op_ = OPERATOR::NONE, const OPERATION& type_ = OPERATION::NONE) :
		sName(s),
		op(op_),
		type(type_),
		operands(NUMTYPE::INTEGER),
		result(NUMTYPE::INTEGER)
	{
	}

	/** Get a pointer to this operator.
	*/
	OperatorType* getPtr() { 
		return this; 
	}
};

class NumericalString {
public:
	std::string str; ///< The string representing the numerical value, name of a defined variable, or a mathematical operator

	unsigned int result; ///< The numerical value, or the result of a previous calculation

	OperatorType* op; ///< Pointer to a mathematical operator which this object represents (undefined if this is not an operator)

	NUMTYPE type; ///< The mathematical type of this value

	bool computed; ///< Flag indicating that this value is the result of a previous calculation

	/** Default constructor.
	*/
	NumericalString() :
		str(),
		result(0),
		op(0x0),
		type(NUMTYPE::INTEGER),
		computed(false)
	{
	}

	/** Integer constructor.
	* @param val Numerical value to initialize to
	*/
	NumericalString(const unsigned int& val);

	/** String constructor.
	* @param s The string representing the numerical value, name of a defined variable, or a mathematical operator
	* @param op_ Pointer to a mathematical operator which this object represents, left undefined if this is not an operator
	*/
	NumericalString(const std::string& s, OperatorType* op_ = 0x0);

	// Assignment operator
	NumericalString& operator = (const unsigned int& n) {
		return ((*this) = NumericalString(n));
	}

	// Arithmetic operators
	NumericalString operator * (const NumericalString& rhs) const {
		return NumericalString(result * rhs.result);
	}
	NumericalString operator / (const NumericalString& rhs) const {
		return NumericalString(result / rhs.result);
	}
	NumericalString operator % (const NumericalString& rhs) const {
		return NumericalString(result % rhs.result);
	}
	NumericalString operator + (const NumericalString& rhs) const {
		return NumericalString(result + rhs.result);
	}
	NumericalString operator - (const NumericalString& rhs) const {
		return NumericalString(result - rhs.result);
	}
	NumericalString operator << (const NumericalString& rhs) const {
		return NumericalString(result << rhs.result);
	}
	NumericalString operator >> (const NumericalString& rhs) const {
		return NumericalString(result >> rhs.result);
	}
	NumericalString operator & (const NumericalString& rhs) const {
		return NumericalString(result & rhs.result);
	}
	NumericalString operator ^ (const NumericalString& rhs) const {
		return NumericalString(result ^ rhs.result);
	}
	NumericalString operator | (const NumericalString& rhs) const {
		return NumericalString(result | rhs.result);
	}

	// Logical operators
	bool operator < (const NumericalString& rhs) const {
		return (result < rhs.result);
	}
	bool operator > (const NumericalString& rhs) const {
		return (result > rhs.result);
	}
	bool operator <= (const NumericalString& rhs) const {
		return (result <= rhs.result);
	}
	bool operator >= (const NumericalString& rhs) const {
		return (result >= rhs.result);
	}
	bool operator == (const NumericalString& rhs) const {
		return (result == rhs.result);
	}
	bool operator != (const NumericalString& rhs) const {
		return (result != rhs.result);
	}
	bool operator && (const NumericalString& rhs) const {
		return (result && rhs.result);
	}
	bool operator || (const NumericalString& rhs) const {
		return (result || rhs.result);
	}

	/** Check if this object represents a mathematical operator whose string representation matches an input string.
	* @param rhs The string representation of a mathematical operator
	* @return True if this object represents an operator and that operator's string representation matches the input string
	*/
	bool operator == (const std::string& rhs) const {
		return (isOperator() && op->sName == rhs);
	}

	/** Check if this object represents a mathematical operator.
	*/
	bool isOperator() const {
		return (op && op->op != OPERATOR::NONE);
	}

	/** Check if this object represents an assignment operator.
	*/
	bool isAssignmentOperator() const {
		return (isOperator() && (op->type == OPERATION::ASSIGNMENT));
	}

	/** Check that the type of this value and a right-hand value matches the required type of a mathematical operator.
	* @param oper The mathematical operator to check for type match
	* @rhs The value of the right-hand operand
	* @return True if the types match, and return false otherwise
	*/
	bool checkTypes(const NumericalString& oper, const NumericalString& rhs) const {
		return (checkType(oper) && rhs.checkType(oper));
	}

	/** Check that the type of this value matches the required type of a mathematical operator.
	* @param oper The mathematical operator to check for type match
	* @return True if the types match, and return false otherwise
	*/
	bool checkType(const NumericalString& oper) const {
		return (type == oper.op->operands);
	}

	virtual NumericalString get() {
		return (*this);
	}

	virtual NumericalString set(const NumericalString& rhs) {
		return (*this = rhs);
	}

	/** Get the required mathematical operand type for this operator.
	*/
	NUMTYPE getOperandType() const {
		return (op->operands);
	}

	/** Get the mathematical type of the output of this operation.
	*/
	NUMTYPE getResultType() const {
		return (op->result);
	}

	/** Get the type of mathematical operator this object represents.
	*/
	OPERATOR getOperator() const {
		return (op->op);
	}

	/** Get the type of operation this object represents.
	*/
	OPERATION getOperatorType() const {
		return (op->type);
	}

	/** Return the current numerical value as an unsigned int.
	*/
	unsigned int getUInt() const {
		return result;
	}

	/** Return the current numerical value as a boolean value.
	*/
	bool getBool() const {
		return (result != 0);
	}

	/** Get a string representing the current numerical value.
	*/
	std::string getStr() const;

	/** Set this value to the result of a mathematical calculation
	* @param res The new numerical value
	* @param newType The type of the new value. If left undefined, the old type is preserved
	*/
	void setResult(const NumericalString& res, const NUMTYPE& newType = NUMTYPE::NONE);
};

class ExternalVariable : public NumericalString {
public:
	ExternalVariable() :
		NumericalString(),
		dtype(CPPTYPE::NONE),
		ptr(0x0)
	{
	}

	/**Pointer constructor.
	* @param val Numerical value to initialize to
	*/
	ExternalVariable(void* val, const CPPTYPE& type_) :
		NumericalString(),
		dtype(type_),
		ptr(val)
	{
	}

	virtual NumericalString get();

	virtual NumericalString set(const NumericalString& rhs);

private:
	CPPTYPE dtype; ///< Type of variable pointed to by ptr

	void* ptr; ///< Pointer to value
};

class OTTTextParser {
public:
	/** Default constructor.
	*/
	OTTTextParser();

	/** String constructor.
	* @param str Compute an input mathematical expression using (see parse())
	*/
	OTTTextParser(const std::string& str);

	/** Toggle debug output on or off
	*/
	void setDebug(bool state = true) {
		debugMode = state;
	}

	/** Check whether or not an input string is a mathematical expression
	* @param str The input string to check
	* @return True if the input string represents a mathematical expression, and return false otherwise
	*/
	bool isExpression(const std::string& str);

	/** Add a user-defined variable definition
	* @param name The name of the variable (case-sensitive)
	* @param value The value of the variable
	*/
	void addDefinition(const std::string& name, const NumericalString& value) {
		defines[name] = value;
	}

	/** Add an externally defined variable definition.
	* @param name The name of the variable (case-sensitive)
	* @param type The data type of the variable
	* @param ptr Pointer to the value
	*/
	void addExternalDefinition(const std::string& name, const CPPTYPE& type, void* ptr) {
		externalDefines[name] = ExternalVariable(ptr, type);
	}

	/** Parse an input mathematical string and compute the result.
	* @param str Input string to parse and compute
	* @param result The returned computational result
	* @return True if the computation was successful, and return false otherwise
	*/
	bool parse(const std::string& str, NumericalString& result);

private:
	bool debugMode; ///< Flag indicating that debug output will be printed
	bool fatalError; ///< Flag indicating that a fatal error has occured

	unsigned int maxOperatorLength; ///< The maximum mathematical operator name length

	NumericalString lastResult; ///< The most recent mathematical result computed by parse()

	std::vector<OperatorType> operators; ///< List of mathematical operators

	std::map<std::string, NumericalString> defines; ///< List of user-defined variables and their values

	std::map<std::string, NumericalString> tempDefines; ///< Temporary list of definitions representing the results of sub-evaluations

	std::map<std::string, ExternalVariable> externalDefines; ///< List of externally defined variables and pointers to their values

	std::map<NUMTYPE, std::string> numTypes; ///< Map of numerical types with user friendly names

	/** Search for a mathematical operator at a specific location in an input string.
	* @param input String to search for an operator
	* @param loc Location in the string to search
	* @param op Returned pointer to a mathematical operator found at the specified location, if one was found
	* @return True if an operator was found and return false otherwise
	*/
	bool findOperatorHere(const std::string& input, const size_t& loc, OperatorType*& op);

	/** Split an input string into parts surrounding mathematical operators.
	* @param str The input string to split into parts
	* @param parts The output vector of numerical values, variables, or operators
	*/
	void splitByOperators(const std::string& str, std::vector<NumericalString>& parts);

	/** Retrieve the requested data from a previous computation or from a defined variable.
	* @param name The input value
	* @param val The returned numerical value or defined variable value
	* @return True if the input value was numerical or if it matches a named variable, and return false otherwise
	*/
	bool getInput(const NumericalString& name, NumericalString& val);

	/** Perform a mathematical computation
	* @param lhs Left hand value of the operation
	* @param rhs Right hand value of the operation
	* @param op Mathematical operation to perform
	* @return True if the computation was completed successfully, and return false otherwise
	*/
	bool compute(NumericalString& lhs, const NumericalString& rhs, const NumericalString& op);

	/** Evaluate a mathematical expression.
	* @param index The current step in the calculation of the full expression string
	* @param str Input mathematical expression
	* @return True if the computation was completed successfully, and return false otherwise
	*/
	bool eval(const unsigned int& index, const std::string& str);

	/** Add a temporary definition representing the results of the most recent sub-string evaluation (i.e. an expression enclosed inside of parentheses)
	* @param index The current step in the calculation of the full expression string
	* @param value The result of the most recent expression evaluation
	*/
	void addTempDefinition(const unsigned int& index, const NumericalString& value);

	/** Add an arithmetic operator to the list of mathematical operators
	* @param name The string representing the operator
	* @param op The mathematical operator
	* @param type The return type for the operator
	*/
	void addArithmeticOperator(const std::string& name, const OPERATOR& op, const NUMTYPE& type = NUMTYPE::INTEGER);

	/** Add a boolean logic operator to the list of mathematical operators
	* @param name The string representing the operator
	* @param op The mathematical operator
	* @param type The return type for the operator
	*/
	void addLogicalOperator(const std::string& name, const OPERATOR& op, const NUMTYPE& type = NUMTYPE::INTEGER);

	/** Add an assignment operator to the list of mathematical operators
	* @param name The string representing the operator
	* @param op The mathematical operator
	* @param type The return type for the operator
	*/
	void addAssignmentOperator(const std::string& name, const OPERATOR& op, const NUMTYPE& type = NUMTYPE::INTEGER);
};

#endif // ifndef OTT_TEXT_PARSER_HPP
