//
// Created by meternal on 4/18/20.
//

#include "TypeSimilarity.h"

namespace ster {
    double TypeSimilarity::TypeSimilarityOfTwoInstruction(const Instruction &_lhs, const Instruction &_rhs) {
        if (_lhs.getOpcode() == _rhs.getOpcode()) return 1 - SAME;
        if (_lhs.getType() == _rhs.getType()) return INSTRUCTION_SAME_TYPE_SIM;
        if (_lhs.getTopType() != _rhs.getTopType()) return 1 - DIFFERENT;
        // lhs and rhs has same TTy below
        if (!_InstructionTopTypeHasSubType(_lhs.getTopType())) {
            return _instructionSameTTyInternalSimilarity[(type_t) _lhs.getTopType()];
        }
        // TODO: subtype similarity
        return 1 - DIFFERENT;
    }

    double TypeSimilarity::TypeSimilarityOfTwoValue(const Value &_lhs, const Value &_rhs) {
        if (_lhs.getTypeid() == _rhs.getTypeid()) return SAME;
        if (_lhs.getType() == _rhs.getType()) return VALUE_SAME_TYPE_SIM;
        // TODO: more detailed Sim
        if ((_lhs.getType() == Value::Type::IntegerTy || _lhs.getType() == Value::Type::FloatTy) &&
            (_rhs.getType() == Value::Type::IntegerTy || _rhs.getType() == Value::Type::FloatTy)) {
            return VALUE_INT_AND_FLOAT_SIM;
        }
        return DIFFERENT;
    }

    bool TypeSimilarity::_InstructionTopTypeHasSubType(Instruction::TopType _chk) {
        switch (_chk) {
            // case Instruction::TopType::MathInst:
            // case Instruction::TopType::OtherInst:
            // return true;
            default:
                return false;
        }
    }

    // Measurement method: Probability of having same function when TTy and param is same
    const double TypeSimilarity::_instructionSameTTyInternalSimilarity[TypeSimilarity::Instruction_TopType_Count] = {
            0.45,   // TerminatorInst
            0.20,   // MathInst
            0.25,   // LogicalOpeInst
            0.40,   // MemoryInst
            0.50,   // ConvertInst
            0.15,   // OtherInst
            0.00    // Unknown
    };
}