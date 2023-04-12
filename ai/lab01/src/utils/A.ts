import {
  calcH,
  getHeuristicChildNodes,
  isSolvable,
  isTarget,
} from '@utils/tools';

export class A {
  sn: aNode; // 起始节点
  en: aNode; // 目标节点
  type: number; // 启发函数类型

  constructor(option: HeuristicOptions, type: number = 1) {
    this.sn = option.startNode;
    this.en = option.endNode;
    this.type = type;

    console.log(`A* 算法使用启发函数 ${type}.`);
  }

  solveEightPuzzles() {
    if (!isSolvable(this.sn.m, this.en.m)) {
      console.log('can not solve.');
      return;
    }

    const open: aNode[] = []; // open 表

    open.push(this.sn);

    const hash = new Map();
    hash.set(this.sn.m.flat().join(','), this.sn);

    // 计算起始点评价函数值
    this.sn.f = calcH(this.type, this.sn.m, this.en.m, 0);

    let count = 0;

    console.log('======查找过程======');
    while (open.length) {
      const curNode = open.shift()!;
      console.log(curNode.m.flat().join(','));
      count++;

      if (isTarget(curNode.m, this.en.m)) {
        // 找到目标结点
        const path = []; // 路径

        // 沿着父节点一路向起点回溯
        let p: aNode | null = curNode;
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
      const cNodes = getHeuristicChildNodes(
        curNode,
        this.en,
        this.type
      );

      cNodes.forEach((item) => {
        const str = item.m.flat().join(',');

        if (!hash.has(str)) {
          // 结点未访问过
          open.push(item);
          hash.set(str, item);
        }
      });

      // 根据评估函数对 open 进行升序
      open.sort((a: aNode, b: aNode) => a.f - b.f);
    }

    console.log('======查找结束======');
  }
}
