import type { FormInstance } from 'antd/es/form';
import Matrix from '@components/matrix';
import {
  useCallback,
  useMemo,
  useRef,
  useState,
} from 'react';
import {
  Select,
  Form,
  Button,
  Space,
  InputNumber,
  Row,
  message,
  Col,
} from 'antd';
import { isMatrixElementEqual } from '@src/utils/tools';
import {
  algorithmOptions,
  numberOptions,
  eightOrigin,
  eightTarget,
  fifteenOrigin,
  fifteenTarget,
  heuristicOptions,
} from '@src/utils/const';
import {
  useRecoilValue,
  useResetRecoilState,
  useSetRecoilState,
} from 'recoil';
import {
  configState,
  loadingState,
  resultState,
} from '@src/store';

interface FormValues {
  algorithm: string;
  target: Matrix;
  origin: Matrix;
  number: number;
  depth?: number;
  heuristic?: number;
}

export default function UserConfig() {
  const formRef = useRef<FormInstance>(null);
  const setConfig = useSetRecoilState(configState);

  const resetResult = useResetRecoilState(resultState);

  const setLoadingState = useSetRecoilState(loadingState);
  const loading = useRecoilValue(loadingState);

  const onReset = useCallback(() => {
    formRef.current!.resetFields();
    setNumber(9);
    resetResult();
    setDfs(false);
    setA(false);
  }, []);

  const [isDfs, setDfs] = useState(false);

  const onAlgorithmChange = useCallback((value: string) => {
    switch (value) {
      case 'dfs': {
        setDfs(true);
        setA(false);
        break;
      }
      case 'A*': {
        setA(true);
        setDfs(false);
        break;
      }
      default: {
        setDfs(false);
        setA(false);
      }
    }
  }, []);

  const [number, setNumber] = useState(9);

  const onNumberChange = useCallback((value: number) => {
    setNumber(value);
  }, []);

  const onFinish = useCallback((value: FormValues) => {
    const isEqual = isMatrixElementEqual(
      value.origin,
      value.target
    );

    if (!isEqual) {
      message.error('起始结点和目标结点不匹配.');
    } else {
      // 设置用户配置
      setConfig({
        algorithm: value.algorithm,
        target: value.target,
        number: value.number,
        depth: value.depth,
        origin: value.origin,
        heuristic: value.heuristic,
      });

      console.log(
        `✨开始计算啦, 即将使用 ${value.algorithm} 算法进行图搜索`
      );

      resetResult(); // 运行前清空结果
      setLoadingState(true);
    }
  }, []);

  const [isA, setA] = useState(false);

  const sub = useMemo(() => {
    if (isDfs) {
      return (
        <Form.Item
          label="搜索深度"
          name="depth"
          style={{ marginBottom: 12 }}
        >
          <InputNumber min={1} max={20} />
        </Form.Item>
      );
    }

    if (isA) {
      return (
        <Form.Item
          label="启发函数"
          name="heuristic"
          style={{ marginBottom: 12 }}
        >
          <Select
            style={{ width: 80 }}
            options={heuristicOptions}
          />
        </Form.Item>
      );
    }
  }, [isDfs, isA]);

  return (
    <Form
      onFinish={onFinish}
      labelAlign="left"
      className="style-form-wrap"
      ref={formRef}
      initialValues={{
        algorithm: algorithmOptions[0].value,
        depth: 4,
        number: 8,
        heuristic: 1,
      }}
    >
      <Space size="large" style={{ width: '100%' }}>
        <Form.Item
          label="算法"
          name="algorithm"
          style={{ marginBottom: 12 }}
        >
          <Select
            style={{ width: 160 }}
            options={algorithmOptions}
            onChange={onAlgorithmChange}
          />
        </Form.Item>
        {sub}
      </Space>
      <Form.Item label="数码" name="number">
        <Select
          style={{ width: 100 }}
          options={numberOptions}
          onChange={onNumberChange}
        />
      </Form.Item>
      <Row>
        <Col span="12" className="style-layout-flex-center">
          <div
            style={{
              marginBottom: 16,
              textAlign: 'center',
            }}
          >
            初始矩阵
          </div>
          <Form.Item
            name="origin"
            style={{ marginBottom: 12 }}
          >
            <Matrix
              num={number}
              init={
                number === 9 ? eightOrigin : fifteenOrigin
              }
            />
          </Form.Item>
        </Col>

        <Col span="12" className="style-layout-flex-center">
          <div
            style={{
              marginBottom: 16,
              textAlign: 'center',
            }}
          >
            目标矩阵
          </div>
          <Form.Item
            name="target"
            style={{ marginBottom: 12 }}
          >
            <Matrix
              num={number}
              init={
                number === 9 ? eightTarget : fifteenTarget
              }
            />
          </Form.Item>
        </Col>
      </Row>
      <Form.Item style={{ marginTop: 12, marginBottom: 0 }}>
        <Row justify="center">
          <Space>
            <Button
              type="primary"
              htmlType="submit"
              loading={loading}
            >
              运行
            </Button>
            <Button htmlType="button" onClick={onReset}>
              重置
            </Button>
          </Space>
        </Row>
      </Form.Item>
    </Form>
  );
}
