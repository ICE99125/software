interface Options {
  startNode: eNode;
  endNode: eNode;
}

type Matrix = number[][];

type BfsOptions = Options;
type DfsOptions = Options;

interface HeuristicOptions {
  startNode: aNode;
  endNode: aNode;
}

interface eNode {
  m: Matrix;
  p: eNode | null; // 父节点
  d: number; // 结点深度
}

interface aNode {
  m: Matrux;
  p: aNode | null;
  g: number; // 耗散值
  f: number; // 启发函数
}
