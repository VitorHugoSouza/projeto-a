'use client'
import Container from '@mui/material/Container';
import { createTheme, ThemeProvider } from '@mui/material/styles';

import Footer from './footer/Footer';
import Header from './header/Header';
import Monitoramento from './monitoramento/Monitoramento';


// TODO remove, this demo shouldn't need to reset the theme.
const defaultTheme = createTheme();

export default function Home() {
  return (
    <ThemeProvider theme={defaultTheme}>
      <Header />
        <Container sx={{ py: 8 }} maxWidth="lg">
          <Monitoramento />
        </Container>
      {/* Footer */}
      <Footer />
      {/* End footer */}
    </ThemeProvider>
  )
}
