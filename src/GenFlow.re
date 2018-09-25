/***
 * Copyright 2004-present Facebook. All Rights Reserved.
 */

open GenFlowCommon;

let signFile = s => s;

let cli = () => {
  let setProjectRoot = Paths.setProjectRoot;
  let checkProjectRoot = () =>
    if (projectRoot^ == "") {
      prerr_endline(
        "Error: command line --setProjectRoot not passed to BS_CMT_POST_PROCESS_CMD.",
      );
      assert(false);
    };
  let setCmtAdd = s => {
    checkProjectRoot();
    let splitColon = Str.split(Str.regexp(":"), s) |> Array.of_list;
    assert(Array.length(splitColon) === 2);
    let cmt: string = splitColon[0];
    let mlast: string = splitColon[1];
    if (Debug.basic) {
      logItem("Add %s  %s\n", cmt, mlast);
    };
    let config = Paths.readConfig();
    cmt |> GenFlowMain.processCmtFile(~signFile, ~config);
    exit(0);
  };
  let setCmtRm = s => {
    checkProjectRoot();
    let splitColon = Str.split(Str.regexp(":"), s) |> Array.of_list;
    assert(Array.length(splitColon) === 1);
    let cmtAbsolutePath: string = splitColon[0];
    /* somehow the CMT hook is passing an absolute path here */
    let cmt = cmtAbsolutePath |> Paths.relativePathFromBsLib;
    let config = Paths.readConfig();
    let outputFile = cmt |> Paths.getOutputFile(~language=config.language);
    if (Debug.basic) {
      logItem("Remove %s\n", cmt);
    };
    if (Sys.file_exists(outputFile)) {
      Unix.unlink(outputFile);
    };
    exit(0);
  };
  let speclist = [
    (
      "--setProjectRoot",
      Arg.String(setProjectRoot),
      "set the root of the bucklescript project. This option is mandatory.",
    ),
    ("-cmt-add", Arg.String(setCmtAdd), "compile a .cmt[i] file"),
    ("-cmt-rm", Arg.String(setCmtRm), "remove a .cmt[i] file"),
  ];
  let usage = "genFlow";
  Arg.parse(speclist, print_endline, usage);
};

cli();