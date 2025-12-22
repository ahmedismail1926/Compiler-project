import { useState, useCallback } from 'react';
import Editor from '@monaco-editor/react';
import axios from 'axios';

// Default sample code
const DEFAULT_CODE = `// Test program for C-Like Compiler

// Variable declarations
int a;
int b = 5;
float c = 3.14;
const int MAX = 100;

// Function declaration
int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

// Main function
void main() {
    // Variable initialization
    a = 10;
    
    // Arithmetic operations
    int sum = a + b;
    int diff = a - b;
    int prod = a * b;
    int quo = a / b;
    int mod = a % b;
    
    // Compound assignment
    sum += 5;
    diff -= 2;
    
    // Relational expressions
    bool isEqual = (a == b);
    bool isGreater = (a > b);
    
    // Logical expressions
    bool andResult = isEqual && isGreater;
    bool orResult = isEqual || isGreater;
    bool notResult = !isEqual;
    
    // Control structures
    if (a > b) {
        a = a + 1;
    } else {
        b = b + 1;
    }
    
    // Loops
    int i = 0;
    while (i < 10) {
        i = i + 1;
    }
    
    for (i = 0; i < 5; i++) {
        if (i == 3) {
            continue;
        }
        a = a + i;
    }
    
    i = 0;
    do {
        i = i + 1;
    } while (i < 5);
    
    // Switch statement
    switch (a) {
        case 10:
            a = 100;
            break;
        case 20:
            a = 200;
            break;
        default:
            a = 0;
    }
    
    // Function call
    int f = factorial(5);
}

`;

type TabType = 'assembly' | 'scope' | 'errors';

interface CompileResult {
  success: boolean;
  assembly: string;
  scope_tree: string;
  errors: string;
}

function App() {
  const [code, setCode] = useState(DEFAULT_CODE);
  const [activeTab, setActiveTab] = useState<TabType>('assembly');
  const [isCompiling, setIsCompiling] = useState(false);
  const [result, setResult] = useState<CompileResult>({
    success: false,
    assembly: '',
    scope_tree: '',
    errors: ''
  });
  const [errorCount, setErrorCount] = useState(0);

  const handleCompile = useCallback(async () => {
    setIsCompiling(true);
    try {
      const formData = new FormData();
      formData.append('code', code);

      const response = await axios.post('/api/compile', formData);
      const data = response.data;
      
      setResult({
        success: data.success,
        assembly: data.assembly || '',
        scope_tree: data.scope_tree || '',
        errors: data.errors || ''
      });

      // Count errors: only count meaningful error lines; treat 'No errors' specially
      const errorsText = (data.errors || '').trim();
      if (/no errors/i.test(errorsText)) {
        setErrorCount(0);
      } else {
        const errorLines = errorsText.split('\n').filter((line: string) => {
          const s = line.trim().toLowerCase();
          return s.includes('error') || s.includes('line [') || /^\d+:\d+/.test(s);
        });
        setErrorCount(errorLines.length);
      }

      // Switch to errors tab if there are errors
      if (!data.success) {
        setActiveTab('errors');
      } else {
        setActiveTab('assembly');
      }
    } catch (error) {
      console.error('Compilation error:', error);
      setResult({
        success: false,
        assembly: '',
        scope_tree: '',
        errors: 'Failed to connect to compiler server. Make sure the server is running on port 5000.'
      });
      setErrorCount(1);
      setActiveTab('errors');
    } finally {
      setIsCompiling(false);
    }
  }, [code]);

  const renderTabContent = () => {
    switch (activeTab) {
      case 'assembly':
        return (
          <pre className="p-4 text-sm font-mono whitespace-pre-wrap text-gray-300">
            {result.assembly || 'Click "Compile" to generate assembly code'}
          </pre>
        );
      case 'scope':
        return (
          <pre className="p-4 text-sm font-mono whitespace-pre-wrap text-gray-300">
            {result.scope_tree || 'Click "Compile" to view symbol table'}
          </pre>
        );
      case 'errors':
        return (
          <pre className={`p-4 text-sm font-mono whitespace-pre-wrap ${result.success ? 'text-success' : 'text-error'}`}>
            {result.errors || 'No compilation results yet'}
          </pre>
        );
    }
  };

  return (
    <div className="h-full flex flex-col bg-dark-bg">
      {/* Navbar */}
      <nav className="h-12 bg-dark-surface border-b border-dark-border flex items-center justify-between px-4">
        <div className="flex items-center gap-3">
          <div className="text-accent font-bold text-lg">⚡</div>
          <h1 className="text-white font-semibold">Poor man's C-Like Compiler</h1>
        </div>
        <button
          onClick={handleCompile}
          disabled={isCompiling}
          className={`px-4 py-1.5 rounded font-medium transition-all ${
            isCompiling
              ? 'bg-gray-600 cursor-not-allowed text-gray-400'
              : 'bg-accent hover:bg-accent-hover text-white'
          }`}
        >
          {isCompiling ? (
            <span className="flex items-center gap-2">
              <svg className="animate-spin h-4 w-4" viewBox="0 0 24 24">
                <circle className="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" strokeWidth="4" fill="none" />
                <path className="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z" />
              </svg>
              Compiling...
            </span>
          ) : (
            '▶ Compile'
          )}
        </button>
      </nav>

      {/* Main Content - Split Pane */}
      <div className="flex-1 flex overflow-hidden">
        {/* Editor Panel */}
        <div className="w-1/2 flex flex-col border-r border-dark-border">
          <div className="h-8 bg-dark-surface border-b border-dark-border flex items-center px-3">
            <span className="text-sm text-gray-400">📄 main.c</span>
          </div>
          <div className="flex-1">
            <Editor
              height="100%"
              defaultLanguage="c"
              theme="vs-dark"
              value={code}
              onChange={(value) => setCode(value || '')}
              options={{
                minimap: { enabled: false },
                fontSize: 14,
                lineNumbers: 'on',
                scrollBeyondLastLine: false,
                automaticLayout: true,
                tabSize: 4,
                wordWrap: 'on',
                folding: true,
                renderLineHighlight: 'line',
              }}
            />
          </div>
        </div>

        {/* Results Panel */}
        <div className="w-1/2 flex flex-col">
          {/* Tabs */}
          <div className="h-10 bg-dark-surface border-b border-dark-border flex items-end px-2">
            <button
              onClick={() => setActiveTab('assembly')}
              className={`px-4 py-2 text-sm font-medium transition-colors ${
                activeTab === 'assembly' ? 'tab-active' : 'tab-inactive'
              }`}
            >
              Assembly
            </button>
            <button
              onClick={() => setActiveTab('scope')}
              className={`px-4 py-2 text-sm font-medium transition-colors ${
                activeTab === 'scope' ? 'tab-active' : 'tab-inactive'
              }`}
            >
              Scope Tree
            </button>
            <button
              onClick={() => setActiveTab('errors')}
              className={`px-4 py-2 text-sm font-medium transition-colors flex items-center gap-2 ${
                activeTab === 'errors' ? 'tab-active' : 'tab-inactive'
              }`}
            >
              Errors
              {errorCount > 0 && (
                <span className="bg-error text-white text-xs px-1.5 py-0.5 rounded-full">
                  {errorCount}
                </span>
              )}
            </button>
          </div>

          {/* Tab Content */}
          <div className="flex-1 overflow-auto bg-dark-bg">
            {renderTabContent()}
          </div>
        </div>
      </div>

      {/* Status Bar */}
      <div className="h-6 bg-accent flex items-center px-3 text-xs text-white">
        <span>{result.success ? '✓ Compilation successful' : (result.errors ? '✗ Compilation failed' : 'Ready')}</span>
        <span className="ml-auto">Line: 1, Column: 1</span>
      </div>
    </div>
  );
}

export default App;
