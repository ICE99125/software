import { Layout } from 'antd';
import UserConfig from '@src/components/userConfig';
import CalcResult from '@components/result';

const { Sider, Content } = Layout;

export default function Contents() {
  return (
    <Layout>
      <Sider theme="light" width="40%">
        <UserConfig></UserConfig>
      </Sider>
      <Content style={{ backgroundColor: '#fff' }}>
        <CalcResult></CalcResult>
      </Content>
    </Layout>
  );
}
