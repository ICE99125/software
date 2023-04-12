import React from 'react';
import ReactDOM from 'react-dom/client';
import App from '@src/App';
import { RecoilRoot } from 'recoil';
import '@src/index.css';
import 'antd/dist/reset.css';

ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
).render(
  <React.StrictMode>
    <RecoilRoot>
      <App />
    </RecoilRoot>
  </React.StrictMode>
);
