#include "cgql/cgqlPch.h"

#include "cgql/type/parser/tokenizer.h"
#include "cgql/logger/logger.h"

namespace cgql {
namespace internal {

const char* tokenTypeToCharArray(const TokenType& type) {
  switch (type) {
    case TokenType::DOCUMENT:
      return "DOCUMENT";
      break;
    case TokenType::OPERATION_DEFINITION:
      return "OPERATION_DEFINITION";
      break;
    case TokenType::SELECTION_SET:
      return "SELECTION_SET";
      break;
    case TokenType::FIELD:
      return "FIELD";
      break;
    case TokenType::NAME:
      return "NAME";
      break;
    case TokenType::INT:
      return "INT";
      break;
    case TokenType::STRING:
      return "STRING";
      break;
    case TokenType::CURLY_BRACES_L:
      return "CURLY_BRACES_L";
      break;
    case TokenType::CURLY_BRACES_R:
      return "CURLY_BRACES_R";
      break;
    case TokenType::BRACES_L:
      return "BRACES_L";
      break;
    case TokenType::BRACES_R:
      return "BRACES_R";
      break;
    case TokenType::SQUARE_BRACES_L:
      return "SQUARE_BRACES_L";
      break;
    case TokenType::SQUARE_BRACES_R:
      return "SQUARE_BRACES_R";
      break;
    case TokenType::START_OF_QUERY:
      return "START_OF_QUERY";
      break;
    case TokenType::END_OF_QUERY:
      return "END_OF_QUERY";
      break;
    case TokenType::COLON:
      return "COLON";
      break;
    case TokenType::BANG:
      return "BANG";
      break;
  }
  return "";
}

// Token
Token::Token(const TokenType& type)
  : type(type) {}
Token::Token(const TokenType& type, const std::string& value)
  : type(type), value(value) {}

Token::~Token() {}

// Tokenizer
Tokenizer::Tokenizer(const char* source)
  : source(source),
    cursor(0),
    current(generateToken(TokenType::START_OF_QUERY)) {}
Tokenizer::~Tokenizer() {}
const Token& Tokenizer::advance() {
  this->current = this->nextToken();
  return this->current;
}

Token generateToken(TokenType type) {
  Token generatedToken(type);
  return generatedToken;
}
Token generateToken(TokenType type, const std::string& value) {
  Token generatedToken(type, value);
  return generatedToken;
}

Token Tokenizer::tokenizeName() {
  uint16_t* i = &this->cursor;
  std::string value; 
  for(; *i < this->source.length();) {
    if(
      isNameContinue(this->source[*i])
    ) {
      value += this->source[*i];
      this->advanceCursor(1);
      continue;
    }
    break;
  }
  return generateToken(
    TokenType::NAME,
    value
  );
}

Token Tokenizer::tokenizeDigits() {
  uint16_t* i = &this->cursor;
  std::string value;
  for(; *i < this->source.length();) {
    if(isDigit(this->source[*i])) {
      value += this->source[*i];
      this->advanceCursor(1);
      continue;
    }
    break;
  }
  return generateToken(
    TokenType::INT,
    value
  );
}

Token Tokenizer::nextToken() {
  uint16_t len = this->source.length();

  uint16_t* i = &this->cursor;

  for(; *i < len; *i = *i + 1) {
    if(isDigit(this->source[*i])) {
      return this->tokenizeDigits();
    }
    if(isNameStart(this->source[*i])) {
      return this->tokenizeName();
    }
    switch ((uint32_t)this->source[*i]) {
      case 0xFEFF:
      case 0x0009:
      case 0x0020:
      case 0x002C:
        continue;
      case 0x007B:
        this->advanceCursor(1);
        return generateToken(TokenType::CURLY_BRACES_L);
      case 0x007D:
        this->advanceCursor(1);
        return generateToken(TokenType::CURLY_BRACES_R);
      case 0x005B:
        this->advanceCursor(1);
        return generateToken(TokenType::SQUARE_BRACES_L);
      case 0x005D:
        this->advanceCursor(1);
        return generateToken(TokenType::SQUARE_BRACES_R);
      case 0x0028:
        this->advanceCursor(1);
        return generateToken(TokenType::BRACES_L);
      case 0x0029:
        this->advanceCursor(1);
        return generateToken(TokenType::BRACES_R);
      case 0x003A:
        this->advanceCursor(1);
        return generateToken(TokenType::COLON);
      case 0x0021:
        this->advanceCursor(1);
        return generateToken(TokenType::BANG);
    }
  }
  return generateToken(TokenType::END_OF_QUERY);
}

void Tokenizer::advanceCursor(int8_t amount) {
  if(this->cursor < this->source.length()) {
    this->cursor += amount;
  }
}

} // internal
} // cgql
