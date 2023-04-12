import {
  getChildNodes,
  isSolvable,
  isTarget,
} from '@utils/tools';

export class DfsEightPuzzles {
  sn: eNode; // 起始节点
  en: eNode; // 目标节点
  depth: number; // 最大深度

  constructor(option: DfsOptions, depth = 4) {
    this.sn = option.startNode;
    this.en = option.endNode;
    this.depth = depth;
  }

  solveEightPuzzles() {
    if (!isSolvable(this.sn.m, this.en.m)) {
      console.log('can not solve.');
      return;
    }

    const stack: eNode[] = [];
    const hash = new Map(); // 用于判断结点是否已经存在过

    stack.push(this.sn); // 起始点入栈
    hash.set(this.sn.m.flat().join(','), this.sn);

    let count = 0;

    console.log('======查找过程======');

    while (stack.length) {
      const curNode = stack.pop()!; // 弹出栈顶元素
      count++;

      console.log(curNode.m.flat().join(','));

      if (isTarget(curNode.m, this.en.m)) {
        // 找到目标结点
        const path = []; // 路径

        // 沿着父节点一路向起点回溯
        let p: eNode | null = curNode;
        while (p) {
          path.push(p);
          p = p.p;
        }

        console.log('======查找结束======');

        return {
          path: path.reverse(),
          count,
        };
      }

      if (curNode.d < this.depth) {
        // 结点扩展
        const cNodes = getChildNodes(curNode);

        cNodes.forEach((item) => {
          const str = item.m.flat().join(',');

          if (!hash.has(str)) {
            // 结点未访问过
            stack.push(item);
            hash.set(str, item);
          }
        });
      }
    }

    console.log('======查找结束======');
  }
}
