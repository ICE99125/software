import {
  loadingState,
  resultState,
  configState,
  ResultState,
} from '@src/store';
import { calcAnswer } from '@src/utils/tools';
import { Row, Col, message, Result } from 'antd';
import { SmileOutlined } from '@ant-design/icons';
import {
  useEffect,
  useMemo,
  useRef,
  useState,
} from 'react';
import { useRecoilValue, useSetRecoilState } from 'recoil';

export default function CalcResult() {
  const loading = useRecoilValue(loadingState);
  const setLoading = useSetRecoilState(loadingState);

  const config = useRecoilValue(configState);

  const setResult = useSetRecoilState(resultState);
  const result = useRecoilValue(resultState);

  const [idx, setIdx] = useState(0);
  const timer = useRef<NodeJS.Timer | null>(null);

  useEffect(() => {
    if (loading) {
      setTimeout(() => {
        calcAnswer(config)
          .then((e: ResultState) => {
            console.log(`🕐本次运行耗时: ${e.time} ms.`);
            console.log(`🔬共查找了 ${e.count} 个节点.`);
            console.log('🎯运算结果为: ', e.path);

            setResult({
              time: e.time,
              path: e.path,
              count: e.count,
            });

            setLoading(false);
            setIdx(0);
          })
          .catch(() => {
            // 没算出答案
            message.error('未找到答案');
            setLoading(false);
          });
      }, 1000);
    }
  }, [loading]);

  useEffect(() => {
    if (result.path.length !== 0) {
      timer.current = setInterval(() => {
        if (idx >= result.path.length - 1) {
          clearInterval(Number(timer.current));
          timer.current = null;
        } else setIdx(idx + 1);
      }, 1000);
    }

    return () => clearInterval(Number(timer.current));
  }, [idx, result]);

  const display = useMemo(() => {
    if (result.path.length == 0) {
      return (
        <Result
          icon={<SmileOutlined />}
          title="开始愉快的搜索吧~"
        />
      );
    } else {
      const p = result.path[idx].m.flat();
      const rowNum = result.path[0].m.length;
      const size = 60; // 方块大小
      const totalNum = rowNum ** 2;
      const span = 24 / result.path[0].m.length;
      const gutter = 8; // 间隔

      return (
        <Row
          gutter={[gutter, gutter]}
          style={{
            width: (size + gutter) * rowNum,
          }}
        >
          {new Array(totalNum).fill(0).map((_, i) => (
            <Col span={span} key={i}>
              <div
                className={
                  p[i] !== 0
                    ? 'style-block'
                    : 'style-no-block'
                }
                style={{
                  width: size,
                  height: size,
                }}
              >
                {p[i] !== 0 ? p[i] : ''}
              </div>
            </Col>
          ))}
        </Row>
      );
    }
  }, [idx, result]);

  return (
    <div className="style-result-wrap">
      <h5>
        耗时: {result.time} ms, 共查找 {result.count} 个节点
      </h5>
      <div className="style-display-result-wrap">
        {display}
      </div>
    </div>
  );
}
