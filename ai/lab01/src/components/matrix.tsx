import { oneToTwo } from '@src/utils/tools';
import { Col, Input, Row } from 'antd';
import {
  useCallback,
  useMemo,
  useState,
  ChangeEvent,
  useEffect,
} from 'react';

interface Matrixprops {
  num: number; // 矩阵大小
  init?: number[]; // 初始值
  onChange?: (m: Matrix) => void;
}

export default function Matrix(props: Matrixprops) {
  const { num, init, onChange } = props;
  const rowNum = Math.sqrt(num); // 单行输入框个数
  const size = 40; // 单个输入框尺寸
  const span = 24 / rowNum; // 每个输入框占比
  const gutter = 5; // 输入框间隔

  const [matrix, setMatrix] = useState<number[]>(
    new Array(num).fill(0)
  );

  useEffect(() => {
    setMatrix([...init!]);
  }, [num]);

  useEffect(() => {
    if (typeof onChange !== 'undefined') {
      onChange(oneToTwo(matrix, rowNum));
    }
  }, [matrix]);

  const oneInputChange = useCallback(
    (e: ChangeEvent<HTMLInputElement>, idx: number) => {
      const m = [...matrix];
      m[idx] = Number(e.target.value);
      setMatrix(m);
    },
    [matrix]
  );

  const inputs = useMemo(() => {
    return new Array(num).fill(0).map((_, idx) => (
      <Col span={span} key={idx}>
        <Input
          type="number"
          style={{
            width: size,
            height: size,
            textAlign: 'center',
          }}
          value={
            matrix[idx] === 0 ? undefined : matrix[idx]
          }
          onChange={(e) => oneInputChange(e, idx)}
        />
      </Col>
    ));
  }, [num, matrix]);

  return (
    <Row
      gutter={[gutter, gutter]}
      style={{
        width: `${(gutter + size) * rowNum}px`,
      }}
    >
      {inputs}
    </Row>
  );
}
