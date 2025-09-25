import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.css'
import App from './App.jsx'
import { Navigation } from './nav.jsx'
import { ClassesTable } from './class_table.jsx'

createRoot(document.getElementById('root')).render(
  <StrictMode>
    <Navigation />
    <ClassesTable />
    <App />
  </StrictMode>,
)
