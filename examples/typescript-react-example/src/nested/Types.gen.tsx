/* TypeScript file generated by genType. */

// tslint:disable-next-line:no-var-requires
const TypesBS = require('./Types.bs');

import {list} from '../../src/shims/ReasonPervasives.shim';

// tslint:disable-next-line:interface-over-type-literal
export type t = number;

// tslint:disable-next-line:interface-over-type-literal
export type typeWithVars = {tag: "TypeWithVarsA", value: [x, y]} | {tag: "TypeWithVarsB", value: z};

// tslint:disable-next-line:interface-over-type-literal
export type tree = {
  readonly label: string, 
  readonly left?: tree, 
  readonly right?: tree
};

// tslint:disable-next-line:interface-over-type-literal
export type selfRecursive = {readonly self: selfRecursive};

// tslint:disable-next-line:interface-over-type-literal
export type mutuallyRecursiveA = {readonly b: mutuallyRecursiveB};

// tslint:disable-next-line:interface-over-type-literal
export type mutuallyRecursiveB = {readonly a: mutuallyRecursiveA};

export const someIntList: list<number> = TypesBS.someIntList;

export const map: <T1,T2>(_1:((_1:T1) => T2), _2:list<T1>) => list<T2> = TypesBS.map;

export const swap: (_1:tree) => tree = TypesBS.swap;

export const selfRecursiveConverter: (_1:selfRecursive) => selfRecursive = function _(Arg1: any) { const result = 
/* WARNING: circular type selfRecursive. Only shallow converter applied. */
  TypesBS.selfRecursiveConverter([Arg1.self]); return {self:result[0]} };

export const mutuallyRecursiveConverter: (_1:mutuallyRecursiveA) => mutuallyRecursiveB = function _(Arg1: any) { const result = 
/* WARNING: circular type mutuallyRecursiveB. Only shallow converter applied. */
  TypesBS.mutuallyRecursiveConverter([[Arg1.b.a]]); return {a:{b:result[0][0]}} };

export const testFunctionOnOptionsAsArgument: <T1,a>(_1:(null | undefined | a), _2:((_1:(null | undefined | a)) => T1)) => T1 = function _(Arg1: any, Arg2: any) { const result = TypesBS.testFunctionOnOptionsAsArgument((Arg1 == null ? undefined : Arg1), Arg2); return result };
