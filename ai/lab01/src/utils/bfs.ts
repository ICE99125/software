import {
  getChildNodes,
  isSolvable,
  isTarget,
} from '@utils/tools';

export class BfsEightPuzzles {
  sn: eNode; // 起始节点
  en: eNode; // 目标节点

  constructor(option: BfsOptions) {
    this.sn = option.startNode;
    this.en = option.endNode;
  }

  solveEightPuzzles() {
    if (!isSolvable(this.sn.m, this.en.m)) {
      console.log('can not solve.');
      return;
    }

    const queue: eNode[] = [];
    const hash = new Map(); // 用于判断结点是否已经存在过

    queue.push(this.sn); // 起始点入队
    hash.set(this.sn.m.flat().join(','), this.sn);

    let count = 0;

    console.log('======查找过程======');
    while (queue.length) {
      const curNode = queue.shift()!; // 队首元素
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

      // 结点扩展
      const cNodes = getChildNodes(curNode);

      cNodes.forEach((item) => {
        const str = item.m.flat().join(',');

        if (!hash.has(str)) {
          // 结点未访问过
          queue.push(item);
          hash.set(str, item);
        }
      });
    }

    console.log('======查找结束======');
  }
}
