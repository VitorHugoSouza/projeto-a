'use client'
import styles from './page.module.css'
import Button from '@mui/material/Button';
import Grid from '@mui/material/Grid';
import Box from '@mui/material/Box';
import Container from '@mui/material/Container';
import { createTheme, ThemeProvider } from '@mui/material/styles';

import Footer from './footer/Footer';
import Header from './header/Header';
import Monitoramento from './monitoramento/Monitoramento';


// TODO remove, this demo shouldn't need to reset the theme.
const defaultTheme = createTheme();

export default function Home() {
  return (
    <>
      <ThemeProvider theme={defaultTheme}>
      <Header />
      <main>
        {/* Hero unit */}
        <Box
          sx={{
            bgcolor: 'background.paper',
            pt: 8,
            pb: 6,
          }}
        >
          <Container maxWidth="sm">
            
          </Container>
        </Box>
        <Container sx={{ py: 8 }} maxWidth="md">
          {/* End hero unit */}
          <Grid container spacing={4}>
            <Monitoramento />
          </Grid>
        </Container>
      </main>
      {/* Footer */}
        <Footer />
      {/* End footer */}
    </ThemeProvider>
    </>
  )
}
