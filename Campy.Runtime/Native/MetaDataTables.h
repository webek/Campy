// Copyright (c) 2012 DotNetAnywhere
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

// NOTE (KED): This meta is version specific; assemblies differ based on the compiler that generated them.


// Forward typedef's (anything used in MetaData.h must be here)
typedef struct tMD_MethodDef_ tMD_MethodDef;
typedef struct tMD_FieldDef_ tMD_FieldDef;
typedef struct tMD_TypeDef_ tMD_TypeDef;
typedef struct tMD_MethodSpec_ tMD_MethodSpec;
typedef struct tMD_ImplMap_ tMD_ImplMap;

#include "Types.h"
#include "JIT.h"
#include "MetaData.h"
#include "Generics.h"

// First, the combined tables

typedef struct tMDC_ToFieldDef_ tMDC_ToFieldDef;
struct tMDC_ToFieldDef_ {
    tMD_FieldDef *pFieldDef;
};

typedef struct tMDC_ToMethodDef_ tMDC_ToMethodDef;
struct tMDC_ToMethodDef_ {
    tMD_MethodDef *pMethodDef;
};

typedef struct tMDC_ToTypeDef_ tMDC_ToTypeDef;
struct tMDC_ToTypeDef_ {
    tMD_TypeDef *pTypeDef;
};


// Second, the raw metadata tables

// Table 0x00 - Module
struct tMD_Module_ {
    int identity;
    // Module name - index into string heap
    STRING name;
    // GUID for module version - index into GUID heap
    GUID_ mvID;
};
typedef struct tMD_Module_ tMD_Module;
#define MD_TABLE_MODULE 0x00

// Table 0x01 - TypeRef
struct tMD_TypeRef_ {
    // Combined
    tMD_TypeDef *pTypeDef;

    int identity;

    // Table index into various tables
    IDX_TABLE resolutionScope;
    // Offset for the name of type ref - index into string heap
    int name_offset;
    // Name of type ref - index into string heap
    STRING name;
    // Offset for the namespace of type ref - index into string heap
    int nameSpace_offset;
    // Namespace of type ref - index into string heap
    STRING nameSpace;
};
typedef struct tMD_TypeRef_ tMD_TypeRef;
#define MD_TABLE_TYPEREF 0x01

// Table 0x02 - TypeDef
struct tMD_TypeDef_ {
    // Combined
    tMD_TypeDef *pTypeDef;

    // MetaData pointer
    tMetaData *pMetaData;
    
    int identity;

    // Type attribute flags
    FLAGS32 flags;
    int name_offset;
    // Name of type def - index into string heap
    STRING name;
    int nameSpace_offset;
    // Namespace of type def - index into string heap
    STRING nameSpace;
    // The type that this type extends (inherits from)
    IDX_TABLE extends;
    // The first entry in the Field table of the fields of this type def
    IDX_TABLE fieldList;
    // The first entry in the Method table of the methods of this type def
    IDX_TABLE methodList;

    // Has this entry had its extended info filled?
    U8 isFilled;
    // Is this the last entry in this table?
    U8 isLast;
    // Is this a value type?
    U8 isValueType;
    // The type of evaluation stack entry needed for this type
    U8 stackType;
    // Total memory size of instances of this type (its in-memory representation) (not static fields)
    U32 instanceMemSize;
    // The parent type definition
    tMD_TypeDef *pParent;
    // The virtual method table
    tMD_MethodDef **pVTable;
    // The number of virtual methods in the vTable
    U32 numVirtualMethods;
    // Pointer to the memory for any static fields in this type. This will be NULL if type has no static fields
    PTR pStaticFields;
    // Has the static constructor been executed yet?
    U8 isTypeInitialised;
    // Is this a generic definition (a generic core type)?
    U8 isGenericDefinition;
    // Is this TypeDef primed - this means that:
    // numPrimedFields, numPrimedMethods, numVirtualMethods
    // have been pre-set.
    U8 isPrimed;
    // padding
    U8 padding0[1];
    // If this type has a static constructor, then store it here. NULL if no static constructor
    tMD_MethodDef *pStaticConstructor;
    // The size of this type when in an array
    U32 arrayElementSize;
    // The size of this type when on the stack (or in a field)
    U32 stackSize;
    // How many interfaces does this type implement
    U32 numInterfaces;
    // All interfaces that this type implements are mapped here
    tInterfaceMap *pInterfaceMaps;
    // The original table index of this TypeDef
    IDX_TABLE tableIndex;
    // If this is a generic type definition, then store any instantiatations here (in a linked list)
    tGenericInstance *pGenericInstances;
    // If this is a generic instance, then store link to its core definition type
    tMD_TypeDef *pGenericDefinition;
    // If this is a generic instance, then store the class type args
    tMD_TypeDef **ppClassTypeArgs;
    // If this type is System.Array, then this stores the element type
    tMD_TypeDef *pArrayElementType;
    // The number of fields in this type. This includes and static fields, but not inherited fields
    U32 numFields;
    // Links to all the fields (in memory order), including statics (not inherited)
    tMD_FieldDef **ppFields;
    // The number of fields in this type and inherited. This includes static fields, and all inherited fields.
    U32 numFieldsAll;
    // Links to all the fields (in memory order), including statics, and inherited.
    tMD_FieldDef **ppFieldsAll;
    // The memory needed for static fields, in bytes
    U32 staticFieldSize;
    // The number of methods in this type. This includes static methods, but not inherited methods
    U32 numMethods;
    // Links to all method in this type, including statics, not inherited
    tMD_MethodDef **ppMethods;
    // If this is a nested class, this records which type it is nested within.
    tMD_TypeDef *pNestedIn;
    // If this type has a finalizer, point to it here
    tMD_MethodDef *pFinalizer;
    // Pointer to the heap object which is the Type class object for this type.
    // This is only allocated as needed, so defaults to NULL
    HEAP_PTR typeObject;
    // for array.
    int rank;
    unsigned int * lengths;
};
typedef struct tMD_TypeDef_ tMD_TypeDef;
#define MD_TABLE_TYPEDEF 0x02

struct tMD_FieldPtr_
{
    // Combined
    tMD_TypeDef *pTypeDef;

    // MetaData pointer
    tMetaData *pMetaData;

    int identity;

};
typedef struct tMD_FieldPtr_ tMD_FieldPtr;
#define MD_TABLE_FIELDPTR 0x03


struct tMD_FieldDef_
{
    // Combined
    tMD_FieldDef *pFieldDef;

    // MetaData pointer
    tMetaData *pMetaData;

    int identity;

    // Flags - FieldAttributes
    FLAGS16 flags;
    // Padding dummy entry
    I16 padding0;
    int name_offset;
    // Name of the field
    STRING name;
    // Signature offset.
    int signature_offset;

    // Signature of the field. Derived field from parsing signature offset.
    BLOB_ signature;
    // The type of this field
    tMD_TypeDef *pType;
    // The type that contains this field
    tMD_TypeDef *pParentType;
    // The field offset within its containing type
    U32 memOffset;
    // The size in bytes that this field takes up in the memory representation
    U32 memSize;
    // The size in bytes of padding just prior to this field. Used in computing the instance size.
    U32 paddingSizeBeforeField;
    // The original table index of this FieldDef
    IDX_TABLE tableIndex;
    // If this is a static field, then the absolute address of this field is stored here.
    // If this field has an RVA, then the pointer to the memory location is stored here.
    // If this is a literal field, then this is a pointer to the tMD_Constant literal definition.
    PTR pMemory;
};
typedef struct tMD_FieldDef_ tMD_FieldDef;
#define MD_TABLE_FIELDDEF 0x04

struct tMD_MethodPtr_
{
    // Combined
    tMD_TypeDef *pTypeDef;

    // MetaData pointer
    tMetaData *pMetaData;

    int identity;
};
typedef struct tMD_MethodPtr_ tMD_MethodPtr;
#define MD_TABLE_METHODPTR 0x05


// Table 0x06 - MethodDef
struct tMD_MethodDef_ 
{
    // Combined
    tMD_MethodDef *pMethodDef;
    // MetaData pointer
    tMetaData *pMetaData;

    int identity;

    // RVA converted to pointer. Code for this method
    U8 *pCIL;
    // Flags - MethodImplAttributes
    FLAGS16 implFlags;
    // Flags - MethodAttribute
    FLAGS16 flags;
    // Name of method
    int name_offset;
    STRING name;
    // Offset into blob for signature.
    int signature_offset;
    // Signature of method
    BLOB_ signature;
    // The first entry in the Param table of the parameters of this method def
    IDX_TABLE paramList;

    // If this method has been JITted, then this points to it
    tJITted *pJITted;
    // Has the extra infomation in this method been filled in yet?
    U8 isFilled;
    // Set true if this method has generic parameters
    U8 isGenericDefinition;
    // The number of parameters for this method. This includes the 'this' parameter if non-static method
    U16 numberOfParameters;
    // The parameter information for this method, including the 'this' parameter if non-static method
    tParameter *pParams;
    // The size in bytes needed for the parameters, including the 'this' parameter if non-static method
    U32 parameterStackSize;
    // The method return type
    tMD_TypeDef *pReturnType;
    // The type that this method is a part of
    tMD_TypeDef *pParentType;
    // The original table index of this MethodDef
    IDX_TABLE tableIndex;
    // If this is a virtual method then this contains the offset into the vTable for this method.
    // This offset is the table index - not the byte offset.
    U32 vTableOfs;
    // If this is method has generic parameters, then store the method type args
    tMD_TypeDef **ppMethodTypeArgs;
    // If this is a generic core method, then store type instances here.
    tGenericMethodInstance *pGenericMethodInstances;

#ifdef GEN_COMBINED_OPCODES
    // The number of times this method is on the call stack of all threads
    U32 callStackCount;
    // The number of times this method has been called
    U64 genCallCount;
    // Pointer to the method that has the next highest number of calls
    tMD_MethodDef *pNextHighestCalls;
    // Pointer to the method that has the prev highest number of calls
    tMD_MethodDef *pPrevHighestCalls;
    // If this method currently has a combined opcode JIT version, then point to it here.
    tJITted *pJITtedCombined;
#endif

#ifdef DIAG_METHOD_CALLS
    // Number of times this method has been called
    U32 callCount;
    // Total time (inclusive of children) in this function
    U64 totalTime;
#endif
};
typedef struct tMD_MethodDef_ tMD_MethodDef;
#define MD_TABLE_METHODDEF 0x06

// Table 0x08 - Param
struct tMD_Param_
{
    int identity;
    // Flags - ParamAttributes
    FLAGS16 flags;
    // The sequence number of the parameter. 0 is the return value, 1+ are the parameters
    U16 sequence;
    // The name of the parameter (optional)
    int name_offset;
    STRING name;
};
typedef struct tMD_Param_ tMD_Param;
#define MD_TABLE_PARAM 0x08

// Table 0x09 - InterfaceImpl
struct tMD_InterfaceImpl_
{
    int identity;
    // The class that implements...
    IDX_TABLE class_;
    // ...this interface
    IDX_TABLE interface_;
};
typedef struct tMD_InterfaceImpl_ tMD_InterfaceImpl;
#define MD_TABLE_INTERFACEIMPL 0x09

// Table 0x0A - MemberRef
struct tMD_MemberRef_
{
    // Combined
    union {
        tMD_MethodDef *pMethodDef;
        tMD_FieldDef *pFieldDef;
    } u;

    int identity;

    // Type of member, coded index: MemberRefParent
    IDX_TABLE class_;
    int name_offset;
    // Name of the member
    STRING name;
    // Offset for the signature of the member
    int signature_offset;
    // Signature of the member
    BLOB_ signature;
};
typedef struct tMD_MemberRef_ tMD_MemberRef;
#define MD_TABLE_MEMBERREF 0x0a

// Table 0x0B - Constant
struct tMD_Constant_
{
    int identity;
    // The ELEMENT_TYPE of the constant - 'void' is ELEMENT_TYPE_CLASS with a 0 blob index
    U8 type;
    // Padding
    U8 padding0[3];
    // The parent of this constant - HasConstant encoded table index
    IDX_TABLE parent;
    // offset for the value of the constant, index in the BLOB heap
    int value_offset;
    // The value of the constant, index in the BLOB heap
    BLOB_ value;
};
typedef struct tMD_Constant_ tMD_Constant;
#define MD_TABLE_CONSTANT 0x0b

// Table 0x0C - CustomAttribute
struct tMD_CustomAttribute_
{
    int identity;
    // Parent
    IDX_TABLE parent;
    // Type
    IDX_TABLE type;
    // Offset for value of attribute
    int value_offset;
    // value of attribute
    BLOB_ value;
};
typedef struct tMD_CustomAttribute_ tMD_CustomAttribute;
#define MD_TABLE_CUSTOMATTRIBUTE 0x0c

// Table 0x0D - FieldMarshal
struct tMD_FieldMarshal_
{
    int identity;
    IDX_TABLE type;
    // Offset for value
    int value_offset;
    BLOB_ value;
};
typedef struct tMD_FieldMarshal_ tMD_FieldMarshal;
#define MD_TABLE_FIELDMARSHAL 0x0d

// Table 0x0E - DeclSecurity
struct tMD_DeclSecurity_
{
    int identity;
    // The security action
    U16 action;
    // Padding
    U16 padding0;
    // The parent typedef, methoddef or assembly of this security info - HasDeclSecurity coded index
    IDX_TABLE parent;
    // Offset for the security permission set
    int permissionSet_offset;
    // The security permission set
    BLOB_ permissionSet;
};
typedef struct tMD_DeclSecurity_ tMD_DeclSecurity;
#define MD_TABLE_DECLSECURITY 0x0e

// Table 0x0F - ClassLayout
struct tMD_ClassLayout_
{
    int identity;
    // The packing size
    U16 packingSize;
    // Padding
    U16 padding0;
    // The class size
    U32 classSize;
    // The parent TypeDef
    IDX_TABLE parent;
};
typedef struct tMD_ClassLayout_ tMD_ClassLayout;
#define MD_TABLE_CLASSLAYOUT 0x0F


struct tMD_FieldLayout_
{
    int identity;
    U32 offset;
    IDX_TABLE field;
};
typedef struct tMD_FieldLayout_ tMD_FieldLayout;
#define MD_TABLE_FIELDLAYOUT 0x10


// Table 0x11 - StandAloneSig
struct tMD_StandAloneSig_
{
    int identity;
    int signature_offset;
    BLOB_ signature;
};
typedef struct tMD_StandAloneSig_ tMD_StandAloneSig;
#define MD_TABLE_STANDALONESIG 0x11

// Table 0x12 - EventMap
struct tMD_EventMap_
{
    int identity;
    // Index into TypeDef table
    IDX_TABLE parent;
    // Index into Event table. Marks the start of a continuous run of events owned by this type.
    IDX_TABLE eventList;
};
typedef struct tMD_EventMap_ tMD_EventMap;
#define MD_TABLE_EVENTMAP 0x12

// Table 0x14 - Event
struct tMD_Event_
{
    int identity;
    // Flags of type eventAttributes
    FLAGS16 eventFlags;
    // Padding
    U16 padding0;
    // The name of the event
    STRING name;
    // The type of this event. A TypeDefOrRef index. This is NOT the type to which this event belongs.
    IDX_TABLE eventType;
};
typedef struct tMD_Event_ tMD_Event;
#define MD_TABLE_EVENT 0x14

// Table 0x15 - PropertyMap
struct tMD_PropertyMap_
{
    int identity;
    // Parent - index into TypeDef table
    IDX_TABLE parent;
    // PropertyList - index into Property table
    IDX_TABLE propertyList;
    // PropertyList - index into Property table
    IDX_TABLE propertyList2;
};
typedef struct tMD_PropertyMap_ tMD_PropertyMap;
#define MD_TABLE_PROPERTYMAP 0x15

// Table 0x17 - Property
struct tMD_Property_
{
    int identity;
    // Flags - PropertyAttributes
    FLAGS16 flags;
    // Padding dummy entry
    I16 padding0;
    // Name
    STRING name;
    // Offset for the type signature
    int typeSig_offset;
    // The type signature
    BLOB_ typeSig;
};
typedef struct tMD_Property_ tMD_Property;
#define MD_TABLE_PROPERTY 0x17

// Table 0x18 - MethodSemantics
struct tMD_MethodSemantics_
{
    int identity;
    // semantics flags - MethodSemanticsAttributes
    FLAGS16 semantics;
    // Padding dummy entry
    I16 padding0;
    // method - entry into MethodDef table
    IDX_TABLE method;
    // HasSemantics coded entry - index into Event or Property tables
    IDX_TABLE association;
};
typedef struct tMD_MethodSemantics_ tMD_MethodSemantics;
#define MD_TABLE_METHODSEMANTICS 0x18

// Table 0x19 - MethodImpl
struct tMD_MethodImpl_
{
    int identity;
    // Index into TypeDef table
    IDX_TABLE class_;
    // The method to use as the interface implementation. Coded index MethodDefOrRef
    IDX_TABLE methodBody;
    // The method declaration that is being overriden. Coded index MethodDefOrRef
    IDX_TABLE methodDeclaration;
};
typedef struct tMD_MethodImpl_ tMD_MethodImpl;
#define MD_TABLE_METHODIMPL 0x19

struct tMD_ModuleRef_
{
    int identity;
    // The module name referenced
    STRING name;
};
typedef struct tMD_ModuleRef_ tMD_ModuleRef;
#define MD_TABLE_MODULEREF 0x1a

// Table 0x1B - TypeSpec
struct tMD_TypeSpec_
{
    // Combined
    tMD_TypeDef *pTypeDef;
    // MetaData pointer
    tMetaData *pMetaData;
    int identity;
    // Offset for the signature of the type
    int signature_offset;
    // The signature of the type
    BLOB_ signature;
};
typedef struct tMD_TypeSpec_ tMD_TypeSpec;
#define MD_TABLE_TYPESPEC 0x1b

struct tMD_ImplMap_
{
    int identity;
    // Mapping flags of type PInvokeAttributes
    U16 mappingFlags;
    // padding
    U16 padding;
    // A MemberForwarded coded index, specifying which member is forwarded. Note that only members are allowed.
    IDX_TABLE memberForwarded;
    // The import name
    STRING importName;
    // The module ref (scope) of the import
    IDX_TABLE importScope;
};
typedef struct tMD_ImplMap_ tMD_ImplMap;
#define MD_TABLE_IMPLMAP 0x1c

// Table 0x1D - FieldRVA
struct tMD_FieldRVA_
{
    int identity;
    // The RVA of the initial data for the field
    void* rva;
    // Index into the field table
    IDX_TABLE field;
};
typedef struct tMD_FieldRVA_ tMD_FieldRVA;
#define MD_TABLE_FIELDRVA 0x1d

// Table 0x20 - Assembly
struct tMD_Assembly_
{
    int identity;
    // Hash algorithm ID of type AssemblyHashAlgorithm
    U32 hashAlgID;
    // Version info
    U16 majorVersion, minorVersion, buildNumber, revisionNumber;
    // Flags - AssemblyFlags
    FLAGS32 flags;
    // Offset for public key
    int publicKey_offset;
    // Public key
    BLOB_ publicKey;
    // String version of public key.
    STRING public_key_str;
    // Name
    STRING name;
    // Culture
    STRING culture;
};
typedef struct tMD_Assembly_ tMD_Assembly;
#define MD_TABLE_ASSEMBLY 0x20

struct tMD_AssemblyRef_
{
    int identity;
    // Version info
    U16 majorVersion, minorVersion, buildNumber, revisionNumber;
    // Flags - AssemblyFlags
    FLAGS32 flags;
    // Offset for public key or token
    int publicKeyOrToken_offset;
    // Public key or token
    BLOB_ publicKeyOrToken;
    // String version of public key.
    STRING public_key_str;
    // Name
    STRING name;
    // Culture
    STRING culture;
    // Offset for hash value.
    int hashValue_offset;
    // Hash value
    BLOB_ hashValue;
};
typedef struct tMD_AssemblyRef_ tMD_AssemblyRef;
#define MD_TABLE_ASSEMBLYREF 0x23


struct tMD_ExportedType_
{
    FLAGS32 flags;
    IDX_TABLE TypeDefId;
    U32 offset_TypeName;
    STRING TypeName;
    U32 offset_TypeNamespace;
    STRING TypeNamespace;
    U16 Implementation;
    U32 identity;
};
typedef struct tMD_ExportedType_ tMD_ExportedType;
#define MD_TABLE_EXPORTEDTYPE 0x27

struct tMD_ManifestResource_
{
    int identity;
    U32 offset;
    FLAGS32 flags;
    // Name
    STRING name;
    // GOT NO IDEA WHAT THIS IS!
    U16 implementation;
};
typedef struct tMD_ManifestResource_ tMD_ManifestResource;
#define MD_TABLE_MANIFESTRESOURCE 0x28

struct tMD_NestedClass_
{
    int identity;
    // The TypeDef of the class that is nested
    IDX_TABLE nestedClass;
    // The TypeDef of the class in which nestedClass is enclosed
    IDX_TABLE enclosingClass;
};
typedef struct tMD_NestedClass_ tMD_NestedClass;
#define MD_TABLE_NESTEDCLASS 0x29

// Table 0x2A - Generic param
struct tMD_GenericParam_
{
    int identity;
    // The number of this generic parameter. Numbered left-to-right, starting from 0
    U16 number;
    // Flags - GenericParamAttributes
    FLAGS16 flags;
    // Owner - the TypeDef or MethodDef that owns this parameter - TypeOrMethodDef coded index
    IDX_TABLE owner;
    // The name of the parameter
    STRING name;
};
typedef struct tMD_GenericParam_ tMD_GenericParam;
#define MD_TABLE_GENERICPARAM 0x2A

// Table 0x2B - MethodSpec
struct tMD_MethodSpec_
{
    int identity;
    // Combined
    tMD_MethodDef *pMethodDef;
    // MetaData pointer
    tMetaData *pMetaData;

    // Index into MethodDef or MethodRef specifying which method this spec refers to
    IDX_TABLE method;
    // Offset for the index into blob heap, holding the signature of this instantiation
    int instantiation_offset;
    // Index into blob heap, holding the signature of this instantiation
    BLOB_ instantiation;
};
typedef struct tMD_MethodSpec_ tMD_MethodSpec;
#define MD_TABLE_METHODSPEC 0x2B

// Table 0x2C - GenericParamConstraint
struct tMD_GenericParamConstraint_
{
    int identity;
    // The generic param that this constraint applies to
    tMD_GenericParam *pGenericParam;
    // The type of the constraint (coded index TypeDefOrRef)
    IDX_TABLE constraint;
};
typedef struct tMD_GenericParamConstraint_ tMD_GenericParamConstraint;
#define MD_TABLE_GENERICPARAMCONSTRAINT 0x2C
