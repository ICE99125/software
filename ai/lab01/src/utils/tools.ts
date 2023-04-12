import { ConfigState, ResultState } from '@src/store';
import { BfsEightPuzzles } from '@utils/bfs';
import { DfsEightPuzzles } from '@utils/dfs';
import { A } from '@utils/A';

// 判断是否可解
export function isSolvable(
  startNode: Matrix,
  endNode: Matrix
): boolean {
  // 拉成一维数组
  const sn = startNode.flat();
  const en = endNode.flat();

  const c1 = reversePairs(sn),
    c2 = reversePairs(en);

  const eight = sn.length === 9 ? true : false;

  if (eight) {
    // 八数码
    if (c1 % 2 === c2 % 2) return true;
    else return false;
  } else {
    // 十五数码
    if (c1 % 3 === c2 % 3) return true;
    else return false;
  }
}

// 计算逆序数
function reversePairs(arr: number[]): number {
  let count = 0;

  for (let i = 0; i < arr.length; i++) {
    for (let j = i + 1; j < arr.length; j++) {
      if (arr[j] !== 0 && arr[j] < arr[i]) {
        count++;
      }
    }
  }

  return count;
}

// 是否是目标矩阵
export function isTarget(
  source: Matrix,
  target: Matrix
): boolean {
  const s = source.flat().join('');
  const t = target.flat().join('');

  return s === t;
}

// 查看目标元素的坐标
export function findIndex(n: Matrix, t: number) {
  for (let i = 0; i < n.length; i++) {
    for (let j = 0; j < n[i].length; j++) {
      if (n[i][j] === t) return [i, j];
    }
  }
}

// 二维数组值拷贝
export function arrayCopy(m: Matrix) {
  const n: Matrix = [];

  for (let i = 0; i < m.length; i++) {
    n.push(m[i].slice());
  }

  return n;
}

// 四个方向(上, 下, 左, 右)
const dirs = [
  [0, -1],
  [0, 1],
  [-1, 0],
  [1, 0],
];

// 扩展子节点
export function getChildNodes(n: eNode): eNode[] {
  const [y, x] = findIndex(n.m, 0)!; // 找到空格所在位置

  const nodes: eNode[] = [];

  const row = n.m.length,
    col = n.m[0].length;

  dirs.forEach((item) => {
    const newNode: eNode = {
      m: arrayCopy(n.m),
      p: n,
      d: n.d + 1,
    };

    const tx = x + item[0],
      ty = y + item[1];

    if (tx >= 0 && tx < col && ty >= 0 && ty < row) {
      const temp = newNode.m[y][x];
      newNode.m[y][x] = newNode.m[ty][tx];
      newNode.m[ty][tx] = temp;

      nodes.push(newNode);
    }
  });

  return nodes;
}

export function getHeuristicChildNodes(
  n: aNode,
  t: aNode,
  type: number // 使用何种启发函数
): aNode[] {
  const [y, x] = findIndex(n.m, 0)!; // 找到空格所在位置

  const nodes: aNode[] = [];

  const row = n.m.length,
    col = n.m[0].length;

  dirs.forEach((item) => {
    const m = arrayCopy(n.m);

    const tx = x + item[0],
      ty = y + item[1];

    if (tx >= 0 && tx < col && ty >= 0 && ty < row) {
      const temp = m[y][x];
      m[y][x] = m[ty][tx];
      m[ty][tx] = temp;

      const newNode: aNode = {
        m,
        p: n,
        g: n.g + 1,
        f: calcH(type, m, t.m, n.g + 1),
      };

      nodes.push(newNode);
    }
  });

  return nodes;
}

export function calcH(
  type: number,
  s: Matrix, // 源二维数组
  t: Matrix, // 目标二维数组
  g: number // 耗散值
) {
  switch (type) {
    case 1:
      return h1(s, t) + g;
    case 2:
      return h2(s, t) + g;
    default:
      return h1(s, t) + g;
  }
}

// 计算回调函数耗时
export function calcTime(id: string, callback: () => any) {
  console.time(`${id}运行耗时`);

  const res = callback();

  console.timeEnd(`${id}运行耗时`);

  return res;
}

// 计算不在位的将牌数
export function h1(source: Matrix, target: Matrix) {
  let count = 0;

  for (let i = 0; i < source.length; i++) {
    for (let j = 0; j < source[i].length; j++) {
      if (source[i][j] === 0) continue;
      if (source[i][j] !== target[i][j]) count++;
    }
  }

  return count;
}

// 计算不在位将牌移动到目标位置最小距离和
export function h2(source: Matrix, target: Matrix) {
  let dis = 0;

  for (let i = 0; i < source.length; i++) {
    for (let j = 0; j < source[i].length; j++) {
      if (source[i][j] === 0) continue;
      if (source[i][j] !== target[i][j]) {
        const [y, x] = findIndex(target, source[i][j])!;

        dis += Math.abs(i - y) + Math.abs(j - x);
      }
    }
  }

  return dis;
}

// 一维数组转二维数组
export function oneToTwo(arr: number[], step: number) {
  const res = [];

  for (let i = 0; i < arr.length; i += step) {
    res.push(arr.slice(i, i + step));
  }

  return res;
}

export function isMatrixElementEqual(
  source: Matrix,
  target: Matrix
) {
  const s = source.flat().sort();
  const t = target.flat().sort();

  return (
    s.length === t.length && s.toString() === t.toString()
  );
}

// 计算结果
export function calcAnswer(
  config: ConfigState
): Promise<ResultState> {
  return new Promise((resolve, reject) => {
    let ai: BfsEightPuzzles | DfsEightPuzzles | A;

    switch (config.algorithm) {
      case 'bfs': {
        ai = new BfsEightPuzzles({
          startNode: {
            m: config.origin,
            d: 0,
            p: null,
          },
          endNode: {
            m: config.target,
            d: 0,
            p: null,
          },
        });

        break;
      }
      case 'dfs': {
        ai = new DfsEightPuzzles(
          {
            startNode: {
              m: config.origin,
              d: 0,
              p: null,
            },
            endNode: {
              m: config.target,
              d: 0,
              p: null,
            },
          },
          config.depth
        );
        break;
      }
      case 'A*': {
        ai = new A(
          {
            startNode: {
              m: config.origin,
              g: 0,
              p: null,
              f: 0,
            },
            endNode: {
              m: config.target,
              g: 0,
              f: 0,
              p: null,
            },
          },
          config.heuristic
        );

        break;
      }
    }

    const startTime = new Date().getTime();

    const res = ai!.solveEightPuzzles();

    const endTime = new Date().getTime();

    if (typeof res !== 'undefined') {
      resolve({
        count: res.count,
        path: res.path,
        time: endTime - startTime,
      });
    } else {
      reject('无解');
    }
  });
}
