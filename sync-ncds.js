const fs = require('fs');
const path = require('path');

// 경로 설정 (폴더 구조에 맞게 수정됨)
const HPP_PATH = path.join(__dirname, 'src/design/NCDS.hpp');
const CSS_PATH = path.join(__dirname, 'src/design/ncds.css');

if (!fs.existsSync(HPP_PATH)) {
    console.error(`❌ 오류: ${HPP_PATH} 파일을 찾을 수 없습니다.`);
    process.exit(1);
}

const hppContent = fs.readFileSync(HPP_PATH, 'utf-8');

// 정규식: Hex 색상 코드 추출 (Color::fromHex(0x...))
const colorRegex = /constexpr\s+Color\s+(\w+)\s*=\s*Color::fromHex\((0x[0-9A-Fa-f]+)\)/g;

let cssVariables = [];
let match;

console.log("🔄 NCDS 변환 시작 (v2)...");

while ((match = colorRegex.exec(hppContent)) !== null) {
    const originalName = match[1]; // 예: Red500, Gray200, White
    const hex = match[2].replace('0x', '#');

    // [핵심 수정] 이름 변환 로직 강화
    // 1. Red500 -> Red-500 (문자와 숫자 사이 분리)
    // 2. ButtonPrimary -> button-primary (CamelCase 분리)
    let kebabName = originalName
        .replace(/([a-z])([A-Z])/g, '$1-$2') // CamelCase -> kebab-case
        .replace(/([a-zA-Z])(\d)/g, '$1-$2') // 문자-숫자 -> 문자-숫자 (Red500 -> red-500)
        .toLowerCase();

    const cssVarName = `--ncds-${kebabName}`;

    cssVariables.push(`  ${cssVarName}: ${hex};`);
    console.log(`✨ 매핑: ${originalName} \t-> ${cssVarName}`);
}

// CSS 파일 내용 작성
const cssContent = `/* * 🤖 NCDS Auto-Generated CSS
 * Source: src/design/NCDS.hpp
 * Updated: ${new Date().toLocaleString()}
 */
:root {
  /* --- Palette Colors --- */
${cssVariables.join('\n')}

  /* --- Manual Tokens (C++ 헤더의 float 값 등) --- */
  --ncds-radius-md: 8px;
  --ncds-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06);
  --ncds-font-sans: "Commerce Sans", "Inter", -apple-system, sans-serif;
}
`;

fs.writeFileSync(CSS_PATH, cssContent);
console.log(`\n✅ 변환 완료! 파일 생성됨: ${CSS_PATH}`);