import { AppBar, CssBaseline, Toolbar, Typography } from "@mui/material";
import SecurityIcon from '@mui/icons-material/Security';

export default function Header() {
  return (
    <>
      <CssBaseline />
      <AppBar position="relative">
        <Toolbar>
          <SecurityIcon sx={{ mr: 2 }} />
          <Typography variant="h6" color="inherit" noWrap>
            SISTEMA DE MONITORAMENTO
          </Typography>
        </Toolbar>
      </AppBar>
    </>
  );
}