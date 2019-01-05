open GenTypeCommon;

let createBucklescriptBlock = "CreateBucklescriptBlock" ++ ".__";

type recordGen = {
  mutable unboxed: int,
  mutable boxed: int,
};

type recordValue = int;

type moduleItemGen = {mutable itemValue: int};

type moduleItem = int;

let blockTagValue = (~config, i) =>
  string_of_int(i) ++ (config.language == TypeScript ? " as any" : "");

let emitRecordAsInt = (~config, recordValue) =>
  recordValue |> blockTagValue(~config);

let recordValueToString = recordValue => recordValue |> string_of_int;

let emitRecordAsBlock =
    (~config, ~args, ~useCreateBucklescriptBlock, recordValue) => {
  useCreateBucklescriptBlock := true;
  createBucklescriptBlock
  |> EmitText.funCall(
       ~args=[
         recordValue |> emitRecordAsInt(~config),
         EmitText.array(args),
       ],
     );
};
let recordGen = () => {unboxed: 0, boxed: 0};

let newRecordValue = (~unboxed, recordGen) =>
  if (unboxed) {
    let v = recordGen.unboxed;
    recordGen.unboxed = recordGen.unboxed + 1;
    v;
  } else {
    let v = recordGen.boxed;
    recordGen.boxed = recordGen.boxed + 1;
    v;
  };

let moduleItemGen = () => {itemValue: 0};

let newModuleItem = moduleItemGen => {
  let v = moduleItemGen.itemValue;
  moduleItemGen.itemValue = moduleItemGen.itemValue + 1;
  v;
};

let emitModuleItem = itemValue => itemValue |> string_of_int;

let emitVariantLabel = (~comment=true, ~polyVariant, label) =>
  if (polyVariant) {
    (comment ? label |> EmitText.comment : "")
    ++ (label |> Btype.hash_variant |> string_of_int);
  } else {
    label;
  };

let emitVariantGetLabel = (~polyVariant, x) =>
  if (polyVariant) {
    x ++ EmitText.array(["0"]);
  } else {
    x ++ "." ++ "tag";
  };

let emitVariantGetPayload = (~numArgs, ~polyVariant, x) =>
  if (polyVariant) {
    x ++ EmitText.array(["1"]);
  } else if (numArgs == 1) {
    x ++ EmitText.array(["0"]);
  } else {
    /* use runtime block as a tuple, hopefully the tag is ignored */
    x;
  };

let emitVariantWithPayload =
    (~label, ~numArgs, ~polyVariant, ~useCreateBucklescriptBlock, x) =>
  if (polyVariant) {
    EmitText.array([label |> emitVariantLabel(~polyVariant), x]);
  } else {
    useCreateBucklescriptBlock := true;
    let args = numArgs == 1 ? [x] |> EmitText.array : x;
    createBucklescriptBlock |> EmitText.funCall(~args=[label, args]);
  };

let jsVariantTag = "tag";
let jsVariantValue = "value";

let emitJSVariantGetLabel = x => x ++ "." ++ jsVariantTag;

let emitJSVariantGetPayload = x => x ++ "." ++ jsVariantValue;

let emitJSVariantWithPayload = (~label, x) =>
  "{"
  ++ jsVariantTag
  ++ ":"
  ++ label
  ++ ", "
  ++ jsVariantValue
  ++ ":"
  ++ x
  ++ "}";

let isMutableObjectField = name =>
  String.length(name) >= 2
  && String.sub(name, String.length(name) - 2, 2) == "#=";

/* Mutable fields, i.e. fields annotated "[@bs.set]"
   are represented as extra fields called "fieldName#="
   preceding the normal field. */
let checkMutableObjectField = (~previousName, ~name) =>
  previousName == name ++ "#=";