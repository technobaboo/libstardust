// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_INPUT_STARDUSTXR_H_
#define FLATBUFFERS_GENERATED_INPUT_STARDUSTXR_H_

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/flexbuffers.h"

#include "ActionInput.hpp"
#include "HandInput.hpp"
#include "PointerInput.hpp"
#include "common.hpp"

namespace StardustXR {

struct InputData;
struct InputDataBuilder;

enum InputDataRaw : uint8_t {
  InputDataRaw_NONE = 0,
  InputDataRaw_Pointer = 1,
  InputDataRaw_Hand = 2,
  InputDataRaw_Action = 3,
  InputDataRaw_MIN = InputDataRaw_NONE,
  InputDataRaw_MAX = InputDataRaw_Action
};

inline const InputDataRaw (&EnumValuesInputDataRaw())[4] {
  static const InputDataRaw values[] = {
    InputDataRaw_NONE,
    InputDataRaw_Pointer,
    InputDataRaw_Hand,
    InputDataRaw_Action
  };
  return values;
}

inline const char * const *EnumNamesInputDataRaw() {
  static const char * const names[5] = {
    "NONE",
    "Pointer",
    "Hand",
    "Action",
    nullptr
  };
  return names;
}

inline const char *EnumNameInputDataRaw(InputDataRaw e) {
  if (flatbuffers::IsOutRange(e, InputDataRaw_NONE, InputDataRaw_Action)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesInputDataRaw()[index];
}

template<typename T> struct InputDataRawTraits {
  static const InputDataRaw enum_value = InputDataRaw_NONE;
};

template<> struct InputDataRawTraits<StardustXR::Pointer> {
  static const InputDataRaw enum_value = InputDataRaw_Pointer;
};

template<> struct InputDataRawTraits<StardustXR::Hand> {
  static const InputDataRaw enum_value = InputDataRaw_Hand;
};

template<> struct InputDataRawTraits<StardustXR::Action> {
  static const InputDataRaw enum_value = InputDataRaw_Action;
};

bool VerifyInputDataRaw(flatbuffers::Verifier &verifier, const void *obj, InputDataRaw type);
bool VerifyInputDataRawVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

struct InputData FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef InputDataBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_UUID = 4,
    VT_INPUT_TYPE = 6,
    VT_INPUT = 8,
    VT_DISTANCE = 10,
    VT_DATAMAP = 12
  };
  const flatbuffers::String *uuid() const {
    return GetPointer<const flatbuffers::String *>(VT_UUID);
  }
  flatbuffers::String *mutable_uuid() {
    return GetPointer<flatbuffers::String *>(VT_UUID);
  }
  StardustXR::InputDataRaw input_type() const {
    return static_cast<StardustXR::InputDataRaw>(GetField<uint8_t>(VT_INPUT_TYPE, 0));
  }
  const void *input() const {
    return GetPointer<const void *>(VT_INPUT);
  }
  template<typename T> const T *input_as() const;
  const StardustXR::Pointer *input_as_Pointer() const {
    return input_type() == StardustXR::InputDataRaw_Pointer ? static_cast<const StardustXR::Pointer *>(input()) : nullptr;
  }
  const StardustXR::Hand *input_as_Hand() const {
    return input_type() == StardustXR::InputDataRaw_Hand ? static_cast<const StardustXR::Hand *>(input()) : nullptr;
  }
  const StardustXR::Action *input_as_Action() const {
    return input_type() == StardustXR::InputDataRaw_Action ? static_cast<const StardustXR::Action *>(input()) : nullptr;
  }
  void *mutable_input() {
    return GetPointer<void *>(VT_INPUT);
  }
  float distance() const {
    return GetField<float>(VT_DISTANCE, 0.0f);
  }
  bool mutate_distance(float _distance = 0.0f) {
    return SetField<float>(VT_DISTANCE, _distance, 0.0f);
  }
  const flatbuffers::Vector<uint8_t> *datamap() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_DATAMAP);
  }
  flatbuffers::Vector<uint8_t> *mutable_datamap() {
    return GetPointer<flatbuffers::Vector<uint8_t> *>(VT_DATAMAP);
  }
  flexbuffers::Reference datamap_flexbuffer_root() const {
    return flexbuffers::GetRoot(datamap()->Data(), datamap()->size());
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_UUID) &&
           verifier.VerifyString(uuid()) &&
           VerifyField<uint8_t>(verifier, VT_INPUT_TYPE) &&
           VerifyOffsetRequired(verifier, VT_INPUT) &&
           VerifyInputDataRaw(verifier, input(), input_type()) &&
           VerifyField<float>(verifier, VT_DISTANCE) &&
           VerifyOffset(verifier, VT_DATAMAP) &&
           verifier.VerifyVector(datamap()) &&
           verifier.EndTable();
  }
};

template<> inline const StardustXR::Pointer *InputData::input_as<StardustXR::Pointer>() const {
  return input_as_Pointer();
}

template<> inline const StardustXR::Hand *InputData::input_as<StardustXR::Hand>() const {
  return input_as_Hand();
}

template<> inline const StardustXR::Action *InputData::input_as<StardustXR::Action>() const {
  return input_as_Action();
}

struct InputDataBuilder {
  typedef InputData Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_uuid(flatbuffers::Offset<flatbuffers::String> uuid) {
    fbb_.AddOffset(InputData::VT_UUID, uuid);
  }
  void add_input_type(StardustXR::InputDataRaw input_type) {
    fbb_.AddElement<uint8_t>(InputData::VT_INPUT_TYPE, static_cast<uint8_t>(input_type), 0);
  }
  void add_input(flatbuffers::Offset<void> input) {
    fbb_.AddOffset(InputData::VT_INPUT, input);
  }
  void add_distance(float distance) {
    fbb_.AddElement<float>(InputData::VT_DISTANCE, distance, 0.0f);
  }
  void add_datamap(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> datamap) {
    fbb_.AddOffset(InputData::VT_DATAMAP, datamap);
  }
  explicit InputDataBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<InputData> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<InputData>(end);
    fbb_.Required(o, InputData::VT_INPUT);
    return o;
  }
};

inline flatbuffers::Offset<InputData> CreateInputData(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> uuid = 0,
    StardustXR::InputDataRaw input_type = StardustXR::InputDataRaw_NONE,
    flatbuffers::Offset<void> input = 0,
    float distance = 0.0f,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> datamap = 0) {
  InputDataBuilder builder_(_fbb);
  builder_.add_datamap(datamap);
  builder_.add_distance(distance);
  builder_.add_input(input);
  builder_.add_uuid(uuid);
  builder_.add_input_type(input_type);
  return builder_.Finish();
}

inline flatbuffers::Offset<InputData> CreateInputDataDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *uuid = nullptr,
    StardustXR::InputDataRaw input_type = StardustXR::InputDataRaw_NONE,
    flatbuffers::Offset<void> input = 0,
    float distance = 0.0f,
    const std::vector<uint8_t> *datamap = nullptr) {
  auto uuid__ = uuid ? _fbb.CreateString(uuid) : 0;
  auto datamap__ = datamap ? _fbb.CreateVector<uint8_t>(*datamap) : 0;
  return StardustXR::CreateInputData(
      _fbb,
      uuid__,
      input_type,
      input,
      distance,
      datamap__);
}

inline bool VerifyInputDataRaw(flatbuffers::Verifier &verifier, const void *obj, InputDataRaw type) {
  switch (type) {
    case InputDataRaw_NONE: {
      return true;
    }
    case InputDataRaw_Pointer: {
      auto ptr = reinterpret_cast<const StardustXR::Pointer *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case InputDataRaw_Hand: {
      auto ptr = reinterpret_cast<const StardustXR::Hand *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case InputDataRaw_Action: {
      auto ptr = reinterpret_cast<const StardustXR::Action *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return true;
  }
}

inline bool VerifyInputDataRawVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyInputDataRaw(
        verifier,  values->Get(i), types->GetEnum<InputDataRaw>(i))) {
      return false;
    }
  }
  return true;
}

inline const StardustXR::InputData *GetInputData(const void *buf) {
  return flatbuffers::GetRoot<StardustXR::InputData>(buf);
}

inline const StardustXR::InputData *GetSizePrefixedInputData(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<StardustXR::InputData>(buf);
}

inline InputData *GetMutableInputData(void *buf) {
  return flatbuffers::GetMutableRoot<InputData>(buf);
}

inline StardustXR::InputData *GetMutableSizePrefixedInputData(void *buf) {
  return flatbuffers::GetMutableSizePrefixedRoot<StardustXR::InputData>(buf);
}

inline bool VerifyInputDataBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<StardustXR::InputData>(nullptr);
}

inline bool VerifySizePrefixedInputDataBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<StardustXR::InputData>(nullptr);
}

inline void FinishInputDataBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<StardustXR::InputData> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedInputDataBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<StardustXR::InputData> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace StardustXR

#endif  // FLATBUFFERS_GENERATED_INPUT_STARDUSTXR_H_
