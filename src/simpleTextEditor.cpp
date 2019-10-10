// https://www.hackerrank.com/challenges/simple-text-editor/problem
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <memory>
#include <map>


class TextBlock {
public:
  TextBlock(const std::string& text, std::size_t pos) 
    : m_text(text)
    , m_startPosition(pos)
  {}

  const std::string& getText() const {
    return m_text;
  }

  std::size_t getStartPos() const {
    return m_startPosition;
  }

  // One beyond end
  std::size_t getEndPos() const {
    return m_startPosition + m_text.length();
  }

  char charAt(std::size_t pos) {
    return m_text[pos - getStartPos()];
  }

private:
  const std::string m_text;
  const std::size_t m_startPosition;
};


std::ostream& operator<<(std::ostream& out, const TextBlock& tb) {
  out << "[" << tb.getStartPos() << "-" << tb.getEndPos() << "]";
  out << tb.getText();
  return out;
}


struct TextDocument;

struct Operation {
  virtual void apply(TextDocument& doci, bool addUndo) = 0;
};


struct TextDocument {

  void addTextNoUndo(const std::string& text) {
    m_text.emplace_back(text, m_text.empty() ? 0 : m_text.back().getEndPos());
  }

  std::vector<TextBlock> m_text;
  std::stack<std::shared_ptr<Operation>> m_undos;
};


std::ostream& operator<<(std::ostream& out, const TextDocument& doc) {
  for (const auto& tb : doc.m_text)
    out << tb;

  return out;
}


struct AddTextOp : public Operation {
  AddTextOp(const std::string text) 
    : m_text(text)
  {}

  void apply(TextDocument& doc, bool addUndo) override;

  const std::string m_text;
};




struct DeleteTextOp : public Operation {
  DeleteTextOp(std::size_t symbols)
  : m_symbolsToDelete(symbols)
  {}

  void apply(TextDocument& doc, bool addUndo) override;

  std::size_t m_symbolsToDelete;
};


void AddTextOp::apply(TextDocument& doc, bool addUndo) {
  doc.addTextNoUndo(m_text);
  if (addUndo)
    doc.m_undos.emplace(std::make_shared<DeleteTextOp>(m_text.length()));
}

void DeleteTextOp::apply(TextDocument& doc, bool addUndo) {
  std::string deletedText;
  deletedText.reserve(m_symbolsToDelete);

  auto symbolsReminded = m_symbolsToDelete;
  while (symbolsReminded != 0) {
    auto lastBlock = doc.m_text.back();
    doc.m_text.pop_back();

    auto symbolsToCopy = symbolsReminded;
    auto  blockSymbolsReminded = lastBlock.getText().length();
    if (symbolsToCopy > blockSymbolsReminded) {
      symbolsToCopy = blockSymbolsReminded;
      blockSymbolsReminded = 0;
    } else {
      blockSymbolsReminded -= symbolsToCopy;
    }


    std::copy(lastBlock.getText().rbegin(), lastBlock.getText().rbegin() + symbolsToCopy, std::back_inserter(deletedText));
    symbolsReminded -= symbolsToCopy;


    if (symbolsReminded == 0) {
      // If we haven't consumed the whole block, we need to restore the part that's left
      if (blockSymbolsReminded != 0) {
        std::string newText{lastBlock.getText().begin(), lastBlock.getText().begin() + blockSymbolsReminded};
        doc.addTextNoUndo(newText);
      }

      if (addUndo) {
        std::reverse(deletedText.begin(), deletedText.end());
        doc.m_undos.push(std::make_shared<AddTextOp>(deletedText));
      }

      continue;
    }
  }
}

struct PrintOp : public Operation {
  PrintOp(std::size_t pos)
  : m_position(pos)
  {}

  void apply(TextDocument& doc, bool) override {
    auto less = [](std::size_t pos, const TextBlock& block) {
      return pos < block.getStartPos();
    };
  
//    std::cout << doc << std::endl;
//    std::cout << "looking for position " << m_position << std::endl;
    auto blockIt = std::upper_bound(doc.m_text.begin(), doc.m_text.end(), m_position, less);
    --blockIt;

//    std::cout << "found block #" << blockIt - doc.m_text.begin() << std::endl;
    std::cout << blockIt->charAt(m_position) << std::endl;

  }

  std::size_t m_position;
};

struct UndoOp : public Operation {
  void apply(TextDocument& doc, bool) override {
    auto op = doc.m_undos.top();
    doc.m_undos.pop();

    op->apply(doc, false);
  }
};




std::shared_ptr<Operation> readAppend(std::istream& in) {
  std::string text;
  in >> text;
  return std::make_shared<AddTextOp>(text);
}

std::shared_ptr<Operation> readDelete(std::istream& in) {
  std::size_t count;
  in >> count;
  return std::make_shared<DeleteTextOp>(count);
}


std::shared_ptr<Operation> readPrint(std::istream& in) {
  std::size_t position;
  in >> position;
  return std::make_shared<PrintOp>(position-1);
}


std::shared_ptr<Operation> readUndo(std::istream&) {
  return std::make_shared<UndoOp>();
}

static std::map<std::size_t, std::shared_ptr<Operation> (*)(std::istream&)> s_operations = {
  {1, readAppend},
  {2, readDelete},
  {3, readPrint},
  {4, readUndo}
};

std::vector<std::shared_ptr<Operation>> readOperations(std::istream& in) {
  std::size_t count;
  in >> count;
  std::vector<std::shared_ptr<Operation>> result;
  result.reserve(count);

  for (std::size_t i = 0; i < count; ++i) {
    int opId;
    in >> opId;

    result.push_back(s_operations[opId](in));
  }
  
  return result;
}


void executeStdIn() {
  auto ops = readOperations(std::cin);
  TextDocument doc;

  for (auto& op : ops) {
    op->apply(doc, true);
   // std::cout << "--> " << doc << std::endl;
  }
}

void simpleTextEditor () {
  executeStdIn();
}

