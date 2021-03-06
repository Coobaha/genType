// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var ImportMyBanner$CommonjsReactExample = require("./ImportMyBanner.bs.js");

var component = ReasonReact.statelessComponent("PageReason");

function onClick(param) {
  console.log("click");
  
}

function make(message, someNumber, extraGreeting, _children) {
  return {
          debugName: component.debugName,
          reactClassInternal: component.reactClassInternal,
          handedOffState: component.handedOffState,
          willReceiveProps: component.willReceiveProps,
          didMount: component.didMount,
          didUpdate: component.didUpdate,
          willUnmount: component.willUnmount,
          willUpdate: component.willUpdate,
          shouldUpdate: component.shouldUpdate,
          render: (function (_self) {
              var greeting = extraGreeting !== undefined ? extraGreeting : "How are you?";
              return React.createElement("div", {
                          onClick: onClick
                        }, ReasonReact.element(undefined, undefined, ImportMyBanner$CommonjsReactExample.make(true, message + (" " + greeting), [])), "someNumber:" + String(someNumber));
            }),
          initialState: component.initialState,
          retainedProps: component.retainedProps,
          reducer: component.reducer,
          jsElementWrapped: component.jsElementWrapped
        };
}

function testBike(x) {
  return x;
}

exports.component = component;
exports.onClick = onClick;
exports.make = make;
exports.testBike = testBike;
/* component Not a pure module */
