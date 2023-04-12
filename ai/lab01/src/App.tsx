import Contents from '@components/contents';

import type { MenuProps } from 'antd';
import { Layout, Menu } from 'antd';

const { Footer, Content, Header } = Layout;

const navItems: MenuProps['items'] = ['八数码'].map(
  (label, key) => ({
    key,
    label,
  })
);

function App() {
  return (
    <Layout className="site-layout">
      <Header className="site-layout-background">
        <Menu
          items={navItems}
          defaultSelectedKeys={['0']}
          mode="horizontal"
        ></Menu>
      </Header>
      <Content
        style={{ flexGrow: 1, padding: '10px 50px' }}
      >
        <div className="site-layout-content">
          <Contents></Contents>
        </div>
      </Content>
      <Footer style={{ textAlign: 'center' }}>
        LianXiaobin ©2022 Created by Ant Design
      </Footer>
    </Layout>
  );
}

export default App;
