import { atom } from 'recoil';

export interface ConfigState {
  algorithm: string;
  origin: Matrix;
  target: Matrix;
  number: number;
  depth?: number;
  heuristic?: number;
}

export const configState = atom<ConfigState>({
  key: 'config',
  default: {
    algorithm: 'bfs',
    origin: [],
    target: [],
    number: 8,
    depth: undefined,
    heuristic: undefined,
  },
});

// 运算状态
export const loadingState = atom<boolean>({
  key: 'loading',
  default: false,
});

export interface ResultState {
  path: aNode[] | eNode[];
  time: number;
  count: number;
}

export const resultState = atom<ResultState>({
  key: 'result',
  default: {
    path: [],
    time: 0,
    count: 0,
  },
});
