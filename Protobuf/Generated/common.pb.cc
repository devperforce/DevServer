// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: common.proto

#include "common.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_common_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_common_2eproto = nullptr;
const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_common_2eproto::offsets[1] = {};
static constexpr ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema* schemas = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::Message* const* file_default_instances = nullptr;

const char descriptor_table_protodef_common_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014common.proto\032 google/protobuf/descript"
  "or.proto*\246\002\n\nProtocolId\022\r\n\tkLoginReq\020\000\022\r"
  "\n\tkLoginRes\020\001\022\r\n\010kPingReq\020\200\004\022\r\n\010kPingRes"
  "\020\201\004\022\023\n\016kPlayerMoveReq\020\200\006\022\023\n\016kPlayerMoveR"
  "es\020\201\006\022\024\n\017kPlayerMoveNoti\020\202\006\022\021\n\014kFindPath"
  "Req\020\220\006\022\021\n\014kFindPathRes\020\221\006\022\026\n\021kChatBroadc"
  "astReq\020\200\010\022\031\n\024kChatBroadcastNotify\020\201\010\022\024\n\017"
  "kChatUnicastReq\020\202\010\022\024\n\017kChatUnicastRes\020\203\010"
  "\022\027\n\022kChatUnicastNotify\020\204\010:D\n\ttype_enum\022\037"
  ".google.protobuf.MessageOptions\030\320\206\003 \001(\0162"
  "\013.ProtocolId\210\001\001b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_common_2eproto_deps[1] = {
  &::descriptor_table_google_2fprotobuf_2fdescriptor_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_common_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_common_2eproto = {
  false, false, 423, descriptor_table_protodef_common_2eproto, "common.proto", 
  &descriptor_table_common_2eproto_once, descriptor_table_common_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_common_2eproto::offsets,
  nullptr, file_level_enum_descriptors_common_2eproto, file_level_service_descriptors_common_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_common_2eproto_getter() {
  return &descriptor_table_common_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_common_2eproto(&descriptor_table_common_2eproto);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ProtocolId_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_common_2eproto);
  return file_level_enum_descriptors_common_2eproto[0];
}
bool ProtocolId_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 512:
    case 513:
    case 768:
    case 769:
    case 770:
    case 784:
    case 785:
    case 1024:
    case 1025:
    case 1026:
    case 1027:
    case 1028:
      return true;
    default:
      return false;
  }
}

PROTOBUF_ATTRIBUTE_INIT_PRIORITY ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier< ::google::protobuf::MessageOptions,
    ::PROTOBUF_NAMESPACE_ID::internal::EnumTypeTraits< ::ProtocolId, ::ProtocolId_IsValid>, 14, false >
  type_enum(kTypeEnumFieldNumber, static_cast< ::ProtocolId >(0));

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>